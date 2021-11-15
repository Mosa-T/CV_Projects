/*
מוסא תחאוך 311590707

רודין חאתקואי 207064353 
*/


$( "#btn" ).click(function(e) {
    console.log("btn clicked");    
    
    let check = true;
    let fname = $("#user_name");
    let femail= $("#email_id"); 
    let frdwhite = $("#rdbt_white_id");
    let frdred = $("#rdbt_red_id");
    let frbgreen = $("#rdbt_green_id");
    let fcolor = $("input[name='first_item']:checked");
    let fsize = $("#fsize option:selected");
    let fmessage = $("#fmessage");
    let fship = $('input[type="checkbox"]');
    let fqunt = $("#fqunt");
    let fplaced = $("#placed");




    
    
    $("#Rname").html("");
    $("#Rquantity").html("");
    $("#Remail").html("");
    $("#Rmessage").html("");
    $("#Rcolor").html("");
    $("#Rsize").html("");
    $("#Rshipping").html("");
    fplaced.html("");

    console.log( $("#user_name").val());
    console.log(fname);
    if(fname.val() == "" ||!fname || fname == null)
    {
        console.log("name empty");
        fname.prop('required',true);
        check = false;
    }
    //check email
    if( (femail.val()== "") || (!validateEmail(femail.val())) )
    {
        console.log("errror: email input");
        femail.prop('required',true);
        check = false;
    }

    if (!$("input[name='first_item']:checked").val()) {
        console.log("radio check not checked");
        frdwhite.prop('required',true);
         check = false;
     }

     if(check == true){
        e.preventDefault();
        console.log("inserting vals into result");
        $("#Rname").html("<h3>"+fname.val()+"</h3>");
        $("#Rquantity").html("<h3>"+fqunt.val()+"</h3>");
        $("#Remail").html("<h3>"+(femail).val()+"</h3>");
        $("#Rmessage").html("<h3>"+fmessage.val()+"</h3>");
        $("#Rcolor").html("<h3>"+fcolor.val()+"</h3>");
        $("#Rsize").html("<h3>"+fsize.val()+"</h3>");
        $("#Rshipping").html("<h3>"+fship.val()+"</h3>");
        fplaced.html("<h3>"+"Thank you, your order has been received"+"</h3>");

        fname.val("");
        fqunt.val("");
        femail.val("");
        fmessage.val("");
        fplaced.val("");
        frdwhite.val("");
        frdred.val("");
        fsize.val("");
        frbgreen.val("");
        fplaced.val("");
        fcolor.val("");

    }
    
  });


function validateEmail($email) {
    var emailReg = /^([\w-\.]+@([\w-]+\.)+[\w-]{2,4})?$/;
    return emailReg.test( $email );
}
