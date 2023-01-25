<html>
<head>
	<title>A test MF</title>
</head>

<body>

<?php
$x0=2;
echo("COAP");
echo true;
$xx = 6;
$sum = $x0+$xx;
$x1=$x0; 
$x2="Ciao";
$x3=FalSe;
$x4 = [3,"co",2];
//$sum1 = $x0+$x4[6]; CAUSES EXCEPTION
//$sum1 = $x0+$x4; CAUSES EXCEPTION
//$sum1 = $x0[6]+$x4;CAUSES EXCEPTION
//$sum1 = $x0[6]+$x4[0]; CAUSES EXCEPTION
$x6 = array(1,2,4);
//$x5 = $x3[0]; CAUSES EXCEPTION
//check
function a(){

	$x="cocococo";
}

//$x10=a($x0,$x1); //CAUSES EXCEPTION
//$x10=a(0,1); CAUSES EXCEPTION
//$x10=a(0,1,true,$x1); CAUSES EXCEPTION
a();
//$sum2 = $x0+a(0); CAUSES EXCEPTION


$b=3;

if(true){
$a = $b;

}
else {
$a=2;
}

if(true){
$a = 3;
$a=3;
}

$s=0;
function aa(){

	$x="cocococo";
}

if(true)
{
$X=0;
//aa($X); CAUSES EXCEPTION
}


?>

</body>
</html>
