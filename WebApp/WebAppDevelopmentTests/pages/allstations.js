$(function(){
 
   
    tdata = {};  // JSON data object that feeds the template
 
        // Retrieve the server data and then initialise the page  
        $.getJSON("/v1/stations.json", function (d) {
        	console.log(d)
        	console.log(d.data)
        	console.log("HERE")
            $.extend(tdata, d.data);
        });
 
        // When AJAX calls are complete parse the template 
        // replacing mustache tags with vars
        $(document).ajaxStop(function () {
        	var template =" <td>{{station_name}}</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td>";
            var renderedPage = Mustache.to_html(template, tdata );
            console.log(tdata);
            $("#gradeX").html( renderedPage );
        });    
});
