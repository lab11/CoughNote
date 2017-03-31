var noble = require('noble')
var moment = require('moment')

var target_id = 1

var cough_service_uuid = 	'c52c02194c8a1f89b9402b308635169c'
var base_station_rdy_uuid = 'c52c02014c8a1f89b9402b308635169c' // sensor sends over cough times in this
var sys_time_uuid =  	 	'c52c02024c8a1f89b9402b308635169c' // we use this to tell sensor we're ready 

var cough_peripheral = null
var cough_service = null
var base_station_rdy_char = null 
var sys_time_char = null
var restart_counter = 0

var base_station_rdy_buf = Buffer.alloc(1, 1)
var sys_time_buf = Buffer.alloc(4)

// Peripheral Callbacks 
function baseWriteCallback(error) {
	console.log("baseWrite callback")
}

function sysTimeWriteCallback(error) {
	console.log("sysTimeWrite cllback")
}

function baseRdyCallback(data, isNoitification) {
	console.log("BASE WRITE WTF")
}

function sysTimeCallback(data, isNoitification) {
	var ctime = moment().unix() 
	var ntime = data.readUInt32LE(0)
	var tdiff = ctime - ntime
	console.log("Time char callback: " + ntime)
	console.log([target_id, ctime, ntime, tdiff])
}

function getSysTimeChar() {
	cough_service.discoverCharacteristics([sys_time_uuid], function(error, characteristics) {
		console.log("Got SysTime char")
		if(error) {throw error}
		if(characteristics.length != 1) {
			console.log("data discovery fucked - SysTime")
			process.exit()
		}
		sys_time_char = characteristics[0]
		sys_time_char.on('data', sysTimeCallback)
		sys_time_char.notify(true, function(error) {
			console.log("SysTime notify set")
			if(error) {throw error}
			var ctime = moment().unix() 
			sys_time_buf.writeUInt32LE(ctime, 0)
			sys_time_char.write(sys_time_buf, false, function(error) {
				console.log("Time Written")
			})
		})
	})
}

function pGetCharacteristics() {
	// Start a chain of getting characteristics. The first part of the chain grabs the base station ready char
	cough_service.discoverCharacteristics([base_station_rdy_uuid], function(error, characteristics) {
		console.log("Got base station ready  char")
		if(error) {throw error}
		if(characteristics.length != 1) {
			console.log("data discovery fucked - BaseStationRdy")
			console.log(characteristics.length)
			process.exit()
		}
		base_station_rdy_char = characteristics[0]
		getSysTimeChar()
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
		var mfgData = peripheral['advertisement']['manufacturerData']
		var periphId = mfgData.readUInt8(2)
		if(periphId == target_id) {
			console.log('Found target CoughDetector')
			noble.stopScanning(function() {
			console.log("Stopped scanning, time to connect")
			cough_peripheral = peripheral
				cough_peripheral.once('disconnect', function() {
					console.log("Disconnect once handler")
				})
				cough_peripheral.connect(function(error) {
					if(error) {throw error}
					console.log("iniital connection")
					setTimeout(pConnectHandler, 100);
				})	
			})
		}
	}
}


noble.on('stateChange', stateCallback)
noble.on('discover', discoverCallback)