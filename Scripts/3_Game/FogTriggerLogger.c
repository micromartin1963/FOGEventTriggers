class FOGTriggerLogger {
	
	void FOGTriggerLogger() {}
	static void Log(string txt) {
		string file_path = "$profile:\\FOGTriggers\\FOGTriggerLog.log";
		FileHandle FOGlogFile = OpenFile(file_path, FileMode.APPEND);
		if (FOGlogFile != 0)
		{
		FPrintln(FOGlogFile, GetDate() + " [FOGLOG] " + txt);
		CloseFile(FOGlogFile);
		}
	}
	

	static private string GetDate()
	{
	int year, month, day, hour, minute, second;
	GetYearMonthDay(year, month, day);
	GetHourMinuteSecond(hour, minute, second);
	string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
	date.Replace(" ", "_");
	date.Replace(".", "-");
	date.Replace(":", "-");
	return date;
	}
}