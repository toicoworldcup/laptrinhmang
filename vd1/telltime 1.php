<?php
$tr = '<tr style="border: 2px solid;">';
$td = '<td style="border: 2px solid">';
$table = '<table style="border: 2px solid; margin: auto;">';
$table .= $tr . $td . date('j M Y') . '</td></tr>';
$table .= $tr . $td . date('H:i:s') . '</td></tr>';
$table .= '</table>';
echo $table;
