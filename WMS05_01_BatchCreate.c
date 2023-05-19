WMS05_01_BatchCreate()
{
	lr_vuser_status_message (lr_eval_string(" - WMS05_01_AppLogon - Iteration {iteration}"));

	lr_start_transaction("WMS05_010__BatchCreate");
	
	lr_save_string("C:\\LoadRunnerFiles\\Optimiza\\","fileLocation");
	
	dvl_file_write(lr_eval_string("\"C:\\Program Files (x86)\\WinSCP\\WinSCP.com\" /command \"open sftp://me2sftp@sftp-service-dev.supplychain.nhs.uk:22/\" \"put -delete %1 /optimiza/optimiza/test/export/oracle/\" \"exit\""),
	    "Name=WMS05_FTP.bat",
	    LAST);
	
	lr_end_transaction("WMS05_010__BatchCreate", LR_AUTO);

	return 0;
}
