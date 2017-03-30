var noble = require('noble')
var csvWriter = require('csv-write-stream')
var moment = require('moment')
var fs = require('fs')

var target_mac = ''

var cough_service_uuid = 'c52c02194c8a1f89b9402b308635169c'
var cough_data_uuid = 	 'c52c02014c8a1f89b9402b308635169c' // sensor sends over cough times in this
var cough_ack_uuid =  	 'c52c02024c8a1f89b9402b308635169c' // we use this to tell sensor we're ready 
var cough_end_uuid =  	 'c52c02034c8a1f89b9402b308635169c' // sensor tells us it's time to disconnect
var cough_id_uuid  = 	 'c52c02044c8a1f89b9402b308635169c' // sensor tells us it's id
var cough_time_uuid =  	 'c52c02054c8a1f89b9402b308635169c' // cough time

var cough_peripheral = null
var cough_service = null
var cough_data_char = null
var cough_ack_char = null
var cough_end_char = null
var cough_id_char = null
var cough_time_char = null
var current_cough_id = null
var restart_counter = 0
var writer = csvWriter({headers: ['UTC TIME']})

var ackBuffer = new Buffer([1])
// Peripheral Callbacks 

function pWriteHandle(error) {
	console.log("Write handle called")
}

function ackWriteCallback(error) {
	console.log("Ack write callback")
}

function writeAck() {
	cough_ack_char.write(ackBuffer, false, ackWriteCallback)
}

function dataCharCallback(data, isNoitification) {
	var cough_time = data.readUIntLE(0,4)
	console.log("Data char callback: " + cough_time)
	writer.write([cough_time])
	writeAck()
}

function timeCharCallback(data, isNoitification) {
	var ntime = data.readUIntLE(0, 4)
	console.log("Time char callback: " + ntime)
	var ctime = moment().unix() 
	var tdiff = ctime - ntime
	writer.write([tdiff])
	cough_ack_char.write(ackBuffer, false, ackWriteCallback)
}

function idCharCallback(data, isNoitification) {
	console.log("Got ID of length: " + data.length)
	console.log("ID: ", + data[0])
	var m_id = data[0]
	fname = "data/" + String(m_id) + "_" + moment().format() + ".csv"
	writer.pipe(fs.createWriteStream(fname))
	cough_ack_char.write(ackBuffer, false, ackWriteCallback)
}

function endCharCallback(data, isNoitification) {
	console.log("End char received")
	cough_peripheral.disconnect(function(error) {
		console.log("disconnect handler")
		if(error) throw error
	})
}

function getTimeChar() {
	cough_service.discoverCharacteristics([cough_time_uuid], function(error, characteristics) {
		console.log("got time char")
		if(error) throw error
	
		cough_time_char	 = characteristics[0]
		cough_time_char.on('data', timeCharCallback) 
		cough_time_char.notify(true, function(error) {
			console.log("time notify set. Char setting done")
			if(error) {throw error}
			cough_ack_char.onc	
			cough_ack_char.write(ackBuffer, false, ackWriteCallback)
		})
	})
}

function getIdChar() {
	cough_service.discoverCharacteristics([cough_id_uuid], function(error, characteristics) {
		console.log("got id char")
		if(error) {throw error}
		cough_id_char = characteristics[0]
		cough_id_char.on('data', idCharCallback)
		cough_id_char.notify(true, function(error) {
			console.log('id notify set')
			if(error) {throw error}
			getTimeChar()
		})
	})
}

function getEndChar() {
	cough_service.discoverCharacteristics([cough_end_uuid], function(error, characteristics) {
		console.log("got end char")
		if(error) {throw error} 
		cough_end_char = characteristics[0]
		cough_end_char.on('data', endCharCallback)
		cough_end_char.notify(true, function(error) {
			console.log("End char notify set")
			if(error) {throw error}
			getIdChar()
		})
	})
}

function getAckChar() {
	cough_service.discoverCharacteristics([cough_ack_uuid], function(error, characteristics) {
		console.log("Got ack char")
		if(error) {throw error}
		cough_ack_char = characteristics[0]
		getEndChar()
	})
}

function pGetCharacteristics() {
	// Gets all the characteristics and sets all their shit.
	cough_service.discoverCharacteristics([cough_data_uuid], function(error, characteristics) {
		console.log("Got data char")
		if(error) {throw error}
		if(characteristics.length != 1) {
			console.log("data discovery fucked")
			process.exit()
		}
		cough_data_char = characteristics[0]
		cough_data_char.on('data', dataCharCallback)
		cough_data_char.notify(true, function(error) {
			console.log("data notify set")
			if(error) {throw error}
			getAckChar()
		})
	})
}

function pConnectHandler() {
	if(cough_peripheral['state'] != 'connected') {
		if(restart_counter++ >= 10) {
			console.log("Shit is fucked")
			process.exit()	
		}
		cough_peripheral.connect(function(error) {
			console.log("Conection bugged, lets retry")
			console.log(cough_peripheral['state'])
			setTimeout(pConnectHandler, 100)			
		})
	}
	else {
		console.log("Connection was successful")
		cough_peripheral.discoverServices([cough_service_uuid], function(error, services) {
			if(error) { throw error; }
			console.log("service found")
			if(services.length != 1) {
				console.log("Problem with service discovery")
				process.exit()
			}
			cough_service = services[0]
			pGetCharacteristics()
		})
	}
}

function pDisconnectedCallback() {

}

// noble state change and adv callbacks 

function stateCallback(callback) {
	if (callback == "poweredOn") {
		console.log("Noble Powered On")
		noble.startScanning()
	}
}

function discoverCallback(peripheral) {
	console.log("Found device")
	if(peripheral['advertisement']['localName'] == 'CoughDet') {
		console.log("Found a cough detector!")
		console.log(peripheral)
	}
}


noble.on('stateChange', stateCallback)
noble.on('discover', discoverCallback)