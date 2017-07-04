
var exec = require('child_process').exec;
var estado = false;
const ipc = require('electron').ipcRenderer
// const manageWindowBtn = document.getElementById('manage');
// manageWindowBtn.addEventListener('click', function (event) {
//
//
//
//   // serialport.list(function (err, ports) {
//   //   ports.forEach(function(port) {
//   //   $('.ports').append('<option value='+port.comName +'>'+port.comName+'</option>');
//   //   console.log(port.comName);
//   //   console.log(port.pnpId);
//   //   console.log(port.manufacturer);
//   //   console.log("++++++++++++++++++++++++++++++++++");
//   //   });
//   //
//   //
//   // });
// });

$( document ).ready( readyFn );



function readyFn( jQuery ) {




    const toggleBtn = document.getElementById('toggle');

    if(estado==false){
      $("#toggle span").text("Ligar");
    }else {
        $("#toggle span").text("Desligar");
    }
    toggleBtn.addEventListener('click', function (event) {
        //ipc.send('toggle')
        if(estado==false){
          $.get("http://192.168.1.99/on", function(data, status){
            alert("Data: " + data + "\nStatus: " + status);
           });
           estado=true;
          $("#toggle span").text("Desligar");
        }else {
          $.get("http://192.168.1.99/off", function(data, status){
            alert("Data: " + data + "\nStatus: " + status);
           });
           $("#toggle span").text("Ligar");
           estado=false;
        }

      })







      ipc.on('is-not-sudo', function (event, sudo) {
          document.getElementById('sudo').innerHTML = `sudo é: ${sudo}`
        })
};
