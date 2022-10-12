class FogTriggerLogger {
	
	void FogTriggerLogger() {}
	static void Log(string txt) {
		string file_path = "$profile:\\FOGTriggers\\FogTriggerLog.log";
		FileHandle foglogFile = OpenFile(file_path, FileMode.APPEND);
		if (foglogFile != 0)
		{
		FPrintln(foglogFile, GetDate() + " [FOGLOG] " + txt);
		CloseFile(foglogFile);
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