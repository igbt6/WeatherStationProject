
$(function(){

        tData = {};  // JSON data object that feeds the template

        // Retrieve the server data and then initialise the page  
        $.getJSON("/v1/stations.json", function (obj) {
            $.extend(tData, obj.data);
        });

        // When AJAX calls are complete parse the template 
        $(document).ajaxStop(function () {
        	var template ='<tr class="odd gradeX center"> <td>{{name}}</td><td>ACTIVE</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td> </tr> ';
            var stationsHTML="";
            for (var i = tData.Stations.length - 1; i >= 0; i--) {
                stationsHTML += Mustache.to_html(template, tData.Stations[i] );
            };
            //console.log(stationsHTML);
            $(".stations-body-tab").append(stationsHTML );
            $(".nr-of-all-stats").replaceWith(tData.Stations.length);
            $('#stations-table').DataTable({ 

                responsive: true

            });
        });
    });


/*
$(function(){$('#stations-table').DataTable({
    
    "processing": true,
    "serverSide": true,
    
    "ajax": {
        "url":"/v1/stations.json", //tdata.Stations[0],
        "dataType": "json",
        "type":"GET"
    },
    "columns": [
        {"data": "name"},
        {"data.Stations": "city"},
        {"data.Stations": "country"},
        {"data.Stations": "date"}
    ]
});

});
*/

