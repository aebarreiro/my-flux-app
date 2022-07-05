<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="main.css">  
	</head>
	<body>
		<div>
<?php
echo "<p>Hello World from" . getenv('MY_NAMESPACE') . "</p>";
echo "<p>I'm on" . getenv('MY_NODE') . "</p>";
?>
		</div>
	</body>
</html>
