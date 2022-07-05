<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="main.css">  
	</head>
	<body>
		<div>
		<?php
			print "<p>Hello World from" . getenv('MY_NAMESPACE') . "</p>";
			print "<p>I'm on" . getenv('MY_NODE') . "</p>";
		?>
		</div>
	</body>
</html>
