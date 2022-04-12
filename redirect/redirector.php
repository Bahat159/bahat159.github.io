<html>
  <head>
	<title>URLRedirector</title>
		<style type="text/css">
		</style>
	</head>
	<body>
    <?php 
    $urls = array("https://www.google.com"); 
    $url = $urls[array_rand($urls)]; 
    header("Location: https://$url"); 
		?>
	</body>
</html>
