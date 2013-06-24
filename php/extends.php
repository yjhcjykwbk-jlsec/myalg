<?php
//	$test=array('hello',array('world','good'),'you');
//	$return=print_r($test);
	class A{
		protected $var;
		static $static="hello";
		public function __construct(){
			$this->var='base';
		}
		public function func(){
			return $this->var;
		}
	}
	class B extends A{
		protected $var;
		public function __construct(){
			$this->var='son';
		}
	}
	class C extends A{static $static;}
$B=new B;
echo $B->func()."<hr>"; //son
$C=new C;
$C::$static="world";
echo $C::$static."<hr>";
echo $B::$static."<hr>";
?>
