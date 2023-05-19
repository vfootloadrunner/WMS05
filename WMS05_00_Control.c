WMS05_00_Control()
{
	dvl_transaction_start("WMS05");

	scriptStatus = Failed;
	
	if (strcmp(DEBUG,"off") == 0) {
		lr_save_datetime("%H:%M:%S",DATE_NOW + (ONE_MIN * (atoi(lr_eval_string("{waitTime}")) /60 )),"iterationTime");
		lr_vuser_status_message (lr_eval_string("Iteration {previousIteration} complete. Next iteration at {iterationTime}"));
		dvl_vts_write(8101,"Columns=depotName|efiStatus|additionalInformation","Row=12","Data=Optimiza|Iteration {previousIteration} complete. Next iteration at {iterationTime}|","Separator=|",LAST);
	
		dvl_think_time(atoi(lr_eval_string("{waitTime}")));
		WMS05_02_FileCreate();
		WMS05_03_FileSend();
	} else {
		lr_error_message("WMS05 is running in DEBUG mode");
		WMS05_99_Debug();
	}

	scriptStatus = Success;
	
	lr_end_transaction("WMS05", LR_AUTO);
	lr_vuser_status_message (lr_eval_string(" - Iteration {iteration} complete. Waiting....."));
	return 0;
}
