
$(function(){
 var initPage= function(){
        tData = {};  // JSON data object that feeds the template

        // Retrieve the server data and then initialise the page  
 /*      $.getJSON("/v1/stations.json", function (obj) {
            $.extend(tData, obj.data);
            console.log("JSON_DATA: "+tData);
        });
*/
$.getJSON("/v1/stations.json" ,
    {format: "json"})
.done(function(json){
    $.extend(tData,json.data);
    console.log("JSON_DATA: "+json.data);

    var template ='<tr class="odd gradeX center"> <td>{{id}}</td><td>{{name}}</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td> </tr> ';
    var stationsHTML="";
    for (var i = tData.Stations.length - 1; i >= 0; i--) {
        stationsHTML += Mustache.to_html(template, tData.Stations[i] );
    };
            //console.log(stationsHTML);
            $(".stations-body-tab").html(stationsHTML );
            $(".nr-of-all-stats").replaceWith(tData.Stations.length);
            var table=   $('#stations-table').DataTable({ 

                responsive: true

            });
            clickOnStation(table);



        })
.fail(function() {
    console.log( "error" );
    alert("Reading Data FUCK UP !")
});

        // When AJAX calls are complete parse the template 
 /*       
        $(document).ajaxStop(function () {
            console.log("HERERERERE !" +tData);
            var template ='<tr class="odd gradeX center"> <td>{{id}}</td><td>{{name}}</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td> </tr> ';
            var stationsHTML="";
            for (var i = tData.Stations.length - 1; i >= 0; i--) {
                stationsHTML += Mustache.to_html(template, tData.Stations[i] );
            };
            //console.log(stationsHTML);
            $(".stations-body-tab").html(stationsHTML );
            $(".nr-of-all-stats").replaceWith(tData.Stations.length);
            var table=   $('#stations-table').DataTable({ 

                responsive: true

            });

            
});*/
}(); });



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

//functions

//events

function clickOnStation(table){
    $('.stations-body-tab').on( 'click', 'tr', function () {
        console.log("TABLE: "+table);
        console.log( table.row( this ).data() );
        var self = this;
        $(this).css('background' , '#000');
        



        $.getJSON("/v1/stations/id/"+table.row( this ).data()[0]+".json" ,
            {format: "json"})
        .done(function(json){
            $.extend(tData,json.data);
            console.log("JSON_DATA: "+json.data + "ADDR: "+"/v1/stations/id/"+(table.row( self ).data()[0])+".json" );

            $.getScript( "/script/station.js" )
            .done(function( script, textStatus ) {
                console.log( textStatus );
                loadStationTemplate( table.row( self ).data());
            }) 
            .fail(function( jqxhr, settings, exception ) {
                console.log( exception );
            });
        })
        .fail(function() {
            console.log( "error" );
            alert("Reading Data FUCK UP !")
        });
        /*var addr = '../../../pages/station/{{id}}.html'*/
     // var stationsHTML = Mustache.to_html(template, table.row( this ).data()[0] );
      //window.location.href = '../../../pages/station/{{id}}.html';
      //window.location.href = '../../../pages/station/{{id}}.html';
       //newStation.loadStationTemplate(table.row( this ).data());

   });
}


$('.stations-body-tab ').on('mouseenter','tr',function () {
 var colour = 
 $(this).css("background", "#8AB800");
}
);

$('.stations-body-tab ').on('mouseleave','tr',function () {
 var colour = 
 $(this).css("background", "white");
}
);
