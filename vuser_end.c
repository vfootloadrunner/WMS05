vuser_end()
{
	if (scriptStatus == Success) {
		lr_vuser_status_message (lr_eval_string(" - Script Completed"));
    	dvl_vts_write(8101,"Columns=depotName|eCommerceStatus","Row=12","Data=Optimiza|Completed {iteration} iterations","Separator=|",LAST);
	} else {
		lr_vuser_status_message (lr_eval_string(" - Script Failed"));
    	dvl_vts_write(8101,"Columns=depotName|eCommerceStatus|","Row=12","Data=Opimiza|Failed after {iteration} iterations|WMS05 - Iteration {previousIteration} failed {errorCheck}","Separator=|",LAST);
	}
	return 0;
}
