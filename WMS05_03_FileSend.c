WMS05_03_FileSend()
{
	char fileData[1024];
	char popenCall[500];
    long filePointer;
    int filesSent = 0;
    
    lr_vuser_status_message (lr_eval_string("WMS05_03_FileSend - Iteration {iteration}"));

	sprintf(popenCall, lr_eval_string("WMS05_FTP.bat {fileLocation}{fileName}.txt"));
	
	lr_save_string("","errorCheck");
    
    dvl_transaction_start("WMS05_030__FileSend");
    
    filePointer = popen(popenCall, "r");
    lr_output_message("%l",filePointer);
 	
	// TODO; Check what the response will be
    while (fgets(fileData, sizeof(fileData), filePointer) != 0) {
    	if (strstr(fileData,".txt") == 0 && strstr(fileData,"|") == 0 && strstr(fileData,"Searching for host...") == 0 && strstr(fileData,"Connecting to host...") == 0 && strstr(fileData,"Authenticating...") == 0 && strstr(fileData,"Using username \"me2sftp\".") == 0 && strstr(fileData,"Authenticating with public key \"imported-openssh-key\" from agent.") == 0 && strstr(fileData,"Authenticated.") == 0 && strstr(fileData,"Starting the session...") == 0 && strstr(fileData,"Session started.") == 0 && strstr(fileData,"Active session: [1] me2sftp@sftp-service-dev.supplychain.nhs.uk") == 0) {
   			dvl_log("--------------------------------------------------------------------------------------------------------------------------------------------------------------------",LAST);
   			dvl_log(fileData,LAST);
   			if (strstr(fileData,"Error") > 0 || strstr(fileData,"error") > 0 || strstr(fileData,"Failed") > 0 || strstr(fileData,"failed") > 0 || strstr(fileData,"Cannot") > 0 || strstr(fileData,"cannot") > 0 || strstr(fileData,"No suc") > 0) {
   				lr_param_sprintf("errorCheck","%s%s",lr_eval_string("{errorCheck}"),fileData);
   			}
   		}
   		if (strstr(fileData,".txt") > 0 && strstr(fileData,"|") > 0) {
  			dvl_log(fileData,LAST);
  			filesSent += 1;
  			lr_output_message ("File sent: %d",filesSent);
  			dvl_transaction_set("BP0501_FilesSent");
  			
  		}
	}
    pclose(filePointer);
    
    if (strcmp(lr_eval_string("{errorCheck}"),"") != 0) {
    	lr_end_transaction("WMS05_030__FileSend", LR_FAIL);
    	lr_exit(LR_EXIT_VUSER,LR_FAIL); 
   	
   	} else if (filesSent == 0) {
    	lr_save_string("Failed files: ","errorCheck");
    	lr_error_message(lr_eval_string("{errorCheck}"));
    	lr_end_transaction("WMS05_030__FileSend", LR_FAIL);
    	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE,LR_FAIL);  
   	
    } else {
    	lr_end_transaction("WMS05_030__FileSend", LR_AUTO);
    }
    
    return 0;
}
