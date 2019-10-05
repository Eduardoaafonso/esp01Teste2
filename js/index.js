var cont = [], hum = [];
var firebase = new Firebase("prototipofikiria.firebaseio.com/");
firebase.on('value', function(snapshot) {
   for(let i in snapshot.val().cont){
     temp.push(snapshot.val().cont[i]);
   }
   for(let i in snapshot.val().hum){
     hum.push(snapshot.val().hum[i]);
   }

  cont = temp.slice(cont.length- 20, cont.length);
  hum = hum.slice(hum.length- 20, hum.length);
  
  drawGraph(cont, hum);
});

function drawGraph(temp, hum){
  var labels = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19];
  var ctx = document.getElementById("myChart").getContext('2d');
var myChart = new Chart(ctx, {
  type: 'line',
  data: {
    labels: labels,
    datasets: [{
    label: "Contador",
    labelString : " ",
    borderColor: 'rgb(255, 99, 132)',
    backgroundColor: 'rgb(255, 99, 132)',
    fill: false,
    data: temp,
      yAxisID: "y-axis-temp",
    },
     {
            label: "humidity [%RH]",
           labelString : "hum",

    borderColor: 'rgb(0, 99, 132)',
    backgroundColor: 'rgb(0, 99, 132)',
    fill: false,
    data: hum,
      yAxisID: "y-axis-temp",       
               
  }]
  },
            options: {
                responsive: true,
              maintainAspectRatio: false,
              hoverMode: 'index',
                stacked: false,
                title:{
                    display: true,
                    text:'Last 20 room measurements'
                },

                scales: {
                    yAxes: [{
                        type: "linear", 
                        display: true,
                        position: "left",
                        id: "y-axis-temp",
                        ticks: {
                          beginAtZero:true,
                          suggestedMax: 50
                        }
              
                    }],
                }
            }
});
}