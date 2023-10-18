console.log(`run with ${process.argv0}: `)
const usb = require('./build/Release/bindings')
usb.test({})