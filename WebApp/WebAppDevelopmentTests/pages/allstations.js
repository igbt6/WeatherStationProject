$(function(){
   console.log("HEREEui");
        tdata = {};  // JSON data object that feeds the template

        // Retrieve the server data and then initialise the page  
        $.getJSON("/v1/stations.json", function (obj) {
            $.extend(tdata, obj.data);
        });

        // When AJAX calls are complete parse the template 
        // replacing mustache tags with vars
        $(document).ajaxStop(function () {
        	var template ="<td>{{name}}</td><td>ACTIVE</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td>";
            console.log(tdata.Stations[0]);
            
            var stationsHTML = Mustache.to_html(template, tdata.Stations[0] );
            console.log(stationsHTML);
            $(".gradeX").replaceWith(stationsHTML );

        });    
    });

<!--
$(function() {
    $('#stations-table').DataTable({
        responsive: true
    });
});

