<!DOCTYPE html>
<html>
	<head>
<?php echo '<link rel="stylesheet" type="text/css" href="main.css">'."\n"; ?>
<style>
  <?php include "main.css" ?>
</style>
	</head>
	<body>
		<div>
<?php
$my_ns = getenv('MY_NAMESPACE') ;
$my_node = getenv('MY_NODE') ;
print "<p>Hello World from " . $my_ns . " </p>\n";
print "<p>I'm on " . $my_node . " </p>\n";
?>
		</div>
	</body>
</html>
