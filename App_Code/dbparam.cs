namespace foldinfoCore.App_Code
{
    public class dbparam
    {
        public string key { get; set; }
        public object value { get; set; }
        public dbparam(string key, object value)
        {
            this.key = key;
            this.value = value;
        }
    }
}