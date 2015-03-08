/*
function loadStationTemplate(stationData){
	if (!stationData) return;
    //console.log(stationData);

        tData = {};  // JSON data object that feeds the template

        var htmlTemplate;
                // Load the HTML template
                $.get("../../../pages/station", function(data){
                    htmlTemplate = data;
                    console.log(htmlTemplate);
                    // When AJAX calls are complete parse the template 
                    var template ='<h1 class="page-header">{{name}}</h1>';
                    var stationHTML="";
                    stationHTML += Mustache.to_html(template, stationData );

                    //window.location = '../../../pages/station/'+stationData[1];
                    $("body").html(htmlTemplate);
                    $(".page-header").html("TEST");

                })
                .fail(function() {
                    alert( "something bad happened" );
                })
                .always(function() {
                    console.log( "finished" );
                });
}

*/




$(function(){

$.get("/content/templates/station.html")
                .done(function(data){
                    htmlTemplate = data;
                    //console.log(htmlTemplate);
                    // When AJAX calls are complete parse the template 
                    var template ='<h1 class="page-header">{{name}}</h1>';
                    var stationHTML="";
                    /*stationHTML += Mustache.to_html(template, stationData );*/

                    //var addr = window.location;
                    var stationName = window.location.search;
                    $("head").append('<link href="/metisMenu/dist/metisMenu.min.css" rel="stylesheet">');
                    $("body").append(htmlTemplate);
                    $("title").html("Weather Stations- station");
                    


                 $.getJSON("/v1/stations/"+stationName.replace('?',"")+".json" ,
                                {format: "json"})


                            .done(function(json){
                                 jData = {};  // JSON data object that feeds the template
                                $.extend(jData,json.data);
                                console.log(jData);

                                var template ='<tr class="odd gradeX center"> <td>{{id}}</td><td>{{name}}</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td> </tr> ';
                             
                                 $(".page-header").html("STATION NAME: "+jData.Station.name);
                                })
                                .fail(function() {
                                    console.log( "error" );
                                    alert("Reading Data FUCK UP !")
                                });



                })
                .fail(function() {
                    alert( "something bad happened" );
                })
                .always(function() {
                    console.log( "finished" );
                });
});

