<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="main.css">  
	</head>
	<body>
		<div>
		<?php
			$my_ns = getenv('MY_NAMESPACE') ;
			$my_node = getenv('MY_NODE') ;
			print "<p>Hello World from" . $my_ns . "</p>";
			print "<p>I'm on" . $my_node . "</p>";
		?>
		</div>
	</body>
</html>
