function drawLineChart() {

    var jsonData = $.ajax({
      url: 'http://tijsluitse.com/iot/eindopdracht/waste.json',
      dataType: 'json',
    }).done(function (results) {

        var labels = [],
            data = [];

        results.forEach(function (result) {
            labels.push(result.time);
            data.push(parseInt(result.waste));
        });

        console.log(labels, data);
      var tempData = {
        labels : labels,
        data: data
      };

      var dataChart = {
                labels: labels,
                datasets: [
                    {
                        label: "LDR",
                        fillColor: "rgba(220,220,220,0.2)",
                        strokeColor: "rgba(220,220,220,1)",
                        pointColor: "rgba(220,220,220,1)",
                        pointStrokeColor: "#fff",
                        pointHighlightFill: "#fff",
                        pointHighlightStroke: "rgba(220,220,220,1)",
                        data: data
                    }
                ]
            };

        var ctx = document.getElementById("linechart").getContext("2d");
        var myLineChart = new Chart(ctx).Line(dataChart);
    });
  }

  drawLineChart();