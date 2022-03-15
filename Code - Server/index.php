<?php
// Copyright 2022 Maciej Kaszkowiak (maciej@kaszkowiak.org)
// Apache License 2.0

// Example valid request: /?secret=YOURSECRETPASWD&mode=<0-9>
$mode = $_GET['mode'];
$right = $_GET['secret'] == 'YOURSECRETPASWD' && is_numeric($mode);

// It passes the MODE parameter to the tuyalights command
if ($right) {
	$mode = (string) intval($mode);
	$output = shell_exec("tuyalights ".$mode);
	echo $output;
} else {
	http_response_code(401);
	echo "unauthorized!";
}
