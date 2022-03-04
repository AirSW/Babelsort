var addon = require('./build/Release/Babelsort')

async function main(){
    while(1){
        let msg = await addon.parseCSV('/home/shay/Downloads/blabla.csv')
        console.log(msg)
    }
}

main()
setInterval(() => {
    console.log("Event loop stuff")
}, 500)