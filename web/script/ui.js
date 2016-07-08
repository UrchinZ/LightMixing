console.log("Note: This page is best viewed on browers that support javascript. Welcome to Light Mixing. Click OK to continue.");
$(document).ready(function(){
	$(".stuff").hide();
	$("#intro").show();
	$("#show").click(function(){
		show();
	});
	$("li").click(function(){
		toggle($(this).prop('id'));
	});
});
function toggle(opt){
	switch (opt){
		case "opt1":
		$(".stuff").hide();
		$("#intro").show();
		console.log("introduction is shown");
		break;
		case "opt2":
		$(".stuff").hide();
		$("#part").show();
		console.log("part list is shown");
		break;
		case "opt3":
		$(".stuff").hide();
		$("#hardware").show();
		console.log("hardware assembly information is shown");
		break;
		case "opt4":
		$(".stuff").hide();
		$("#software").show();
		console.log("software description is shown");
		break;
		case "opt5":
		$(".stuff").hide();
		$("#exe").show();
		console.log("exercises are shown");
		break;
	}	
}

function show(){
	var name = $("#show").text();
	console.log(name);
	if(name == "Show All"){
		console.log("Show All is clicked");
		$("#show").text("Hide All");
		$(".stuff").show();
	} else {
		$("#show").text("Show All");
		$(".stuff").hide();
		$("#intro").show();
	}
}