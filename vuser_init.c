vuser_init()
{
	DEBUG = lr_get_attrib_string("DEBUG");

	lr_load_dll("Duval.dll");

	dvl_initialise();
	
	dvl_log("FileName",
		"Header=TRUE",
		LAST);
		
	scriptStatus = Success;
	
	lr_save_string("0","waitTime");
	lr_save_string("0","previousIteration");
	
	return 0;
}
