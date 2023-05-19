WMS05_02_FileCreate()
{
	lr_vuser_status_message (lr_eval_string(" - WMS05_02_FileCreate - Iteration {iteration}"));

	lr_start_transaction("WMS05_020__FileCreate");
	
	dvl_vts_read(8019,"Columns=fileName:fileData:additionalDays:fileCreatedDate:waitTime","Pop=true",LAST);
	
	lr_save_datetime("%d%m%Y", DATE_NOW + (ONE_DAY * atoi(lr_eval_string("{additionalDays}"))), "deliveryDate");
	                 
	dvl_string_replace("{fileData}",
		"Remove=XXXXXXXX",
		"Replacement={deliveryDate}",
		LAST);
	
	dvl_file_write("{fileData}",
	    "Name={fileName}.txt",
		"Location={fileLocation}",
		LAST);
	
	// FILE FORMAT
	// Depot|NPC   |Quantity|Required Date|Re-order Group|MS Planner Email|Supplier Number|Supplier Name
	// 928  |FDF033|10.00   |21052021     |MS            |caukett@dxc.com |02887200       |SMITHS MEDICAL INTERNATIONAL LTD
	
	dvl_vts_read(8019,"Columns=waitTime","Pop=false",LAST);
	
	lr_save_string(lr_eval_string("{iteration}"),"previousIteration");
	
	dvl_log("{fileName}",LAST);
	
	lr_end_transaction("WMS05_020__FileCreate", LR_AUTO);
	
	return 0;
}
