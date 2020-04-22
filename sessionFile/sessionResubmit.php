<?php
$SID = session_id();
if(empty($SID)) session_start() or exit(basename(__FILE__).'(): Could not start session');
$_SESSION['err'] = ''; $exit = false;
do {
    //    check if form was previously submitted
    if(isset($_POST['submit']) and isset($_POST['SID']) and ($_POST['SID'] !== session_id())) {
        $ret = null; $exit = true; break; }
    //    break out of do-while if form has not been submitted yet
    if(empty($_POST['submit'])) break;
    //    process form data if user hit form "submit" button
    if(isset($_POST['submit'])) {
        $ret = validate_form();
        //    ret will be error message if form validation failed
        if(is_string($ret)) { $_SESSION['err'] = $ret; break; }
        //    ret will be array of cleaned form values if validation passed
        if(is_array($ret)) { session_regenerate_id(true); $exit = true; break; }
    }
} while(false);

if($exit) display_receipt($ret);
$exit and exit;

function validate_form() {
    $tmp = htmlspecialchars(strtoupper($_POST['name']));    //    clean POST data
    if(stripos($_POST['great'], 'yes') !== false) return array('name' => $tmp, 'great' => 'YES!');
    return 'Wrong answer!';
}

function display_receipt($msg) {
    if($msg === null) echo 'You already answered the question!';
    if(is_array($msg)) echo 'Your answer of '.$msg['great'].' is right '.$msg['name'];
    return;
}
?>

<html><body>
<?php echo $_SESSION['err']; ?>
<form name="form1" action="http://<?php echo $_SERVER['HTTP_HOST'], $_SERVER['PHP_SELF']; ?>" method="post">
Name: <input type="text" name="name" value="<?php isset($_SESSION["name"]) and print $_SESSION["name"]; ?>">
Is PHP great? <input type="text" name="great" value="<?php isset($_SESSION["great"]) and print $_SESSION["great"]; ?>">
<input type="hidden" name="SID" value="<?php echo session_id(); ?>">
<input type="submit" name="submit" value="Submit">
</form></body></html>
