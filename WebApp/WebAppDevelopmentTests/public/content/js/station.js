
//$(function(){
	 function loadStationTemplate(stationData){
	if (!stationData) return;

        tData = {};  // JSON data object that feeds the template

        var htmlTemplate;
                // Load the HTML template
        $.get("../../../pages/station.html", function(data){
            htmlTemplate = data;
        });
        window.location = '../../../pages/station.html';
        console.log(htmlTemplate);
        // Retrieve the server data and then initialise the page  
        /*$.getJSON("/v1/station.json", function (obj) {
            $.extend(tData, obj.data);
        });
*/

        // When AJAX calls are complete parse the template 

        $(document).ajaxStop(function () {
           /* var template ='<tr class="odd gradeX center"> <td>{{id}}</td><td>{{name}}</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td> </tr> ';
            var stationsHTML="";
            for (var i = tData.Stations.length - 1; i >= 0; i--) {
                stationsHTML += Mustache.to_html(template, tData.Stations[i] );
            };*/
            //console.log(stationsHTML);
            $("body").html(htmlTemplate);



        });
}

//});
