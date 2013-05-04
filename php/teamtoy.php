<?php 
$api = 'http://ttsite.sinaapp.com/index.php?c=api';

// 获取Token
$info = json_decode( file_get_contents( $api .'&a=user_get_token&email=' . urlencode('we@teamtoy.net') . '&password='. urlencode('think_different')  ) , true ) ;
$token = $info['data']['token'];

// 取得团队成员名单
print_r( json_decode(file_get_contents($api.'&a=team_members&token='.$token), true  ) );
?> 
