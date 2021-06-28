using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace foldinfoCore.Models
{
    public class userData
    {
        public string userid { get; set; }
    }

    public class userModels
    {
        [Required]
        public string newid { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class loginData
    {
        public string userid { get; set; }
        public string password { get; set; }
        public string longitude { get; set; }
        public string latitude { get; set; }
        //public string browser { get; set; }
    }

    public class loginModels
    {
        [Required]
        public string newid { get; set; }
        [Required]
        public string name { get; set; }
        [Required]
        public string allname { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class otherData
    {
        public string userid { get; set; }
        public string values { get; set; }
    }

    public class signupData
    {
        public string userid { get; set; }
        public string password { get; set; }
        public string username { get; set; }
        public string birthday { get; set; }
    }

    public class itemsModels
    {
        [Required]
        public bool showItem { get; set; }
        [Required]
        public List<Dictionary<string, object>> items { get; set; }
    }

    public class itemModels
    {
        [Required]
        public List<Dictionary<string, object>> items { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class iIconData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public List<Dictionary<string, object>> qaitems { get; set; }
        public string newid { get; set; }
    }
    public class sSecuModels
    {
        [Required]
        public List<Dictionary<string, object>> deviceitems { get; set; }
        [Required]
        public string status { get; set; }
    }
    public class iSecuData
    {
        public string externip { get; set; }
        public string newid { get; set; }
    }

    public class sNotiModels
    {
        [Required]
        public bool generalShow { get; set; }
        [Required]
        public bool mixinalShow { get; set; }
        [Required]
        public bool projectShow { get; set; }
        [Required]
        public bool signoutShow { get; set; }
        [Required]
        public bool processShow { get; set; }
        [Required]
        public bool personsShow { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class iNotiData
    {
        public bool isbool { get; set; }
        public string newid { get; set; }
    }

    public class sRowsData
    {
        public string formId { get; set; }
        public string value { get; set; }
        public string newid { get; set; }
    }

    public class sRowsModels
    {
        [Required]
        public string formId { get; set; }
        [Required]
        public string tile { get; set; }
        [Required]
        public List<Dictionary<string, object>> items { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class dFormData
    {
        public string formId { get; set; }
        public string newid { get; set; }
    }

    public class statusModels
    {
        [Required]
        public string status { get; set; }
    }

    public class permissModels
    {
        [Required]
        public bool insert { get; set; }
        [Required]
        public bool update { get; set; }
        [Required]
        public bool delete { get; set; }
        [Required]
        public bool export { get; set; }
    }

    public class sOptonModels
    {
        [Required]
        public List<Dictionary<string, object>> items { get; set; }
    }

    public class sSiteModels
    {
        [Required]
        public bool images { get; set; }
        [Required]
        public bool videos { get; set; }
        [Required]
        public bool audios { get; set; }
        [Required]
        public string src { get; set; }
        [Required]
        public string imagePath { get; set; }
        [Required]
        public string original { get; set; }
        [Required]
        public string encryption { get; set; }
        [Required]
        public string extension { get; set; }
        [Required]
        public string date { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class iItemsData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public string newid { get; set; }
    }

    public class iFileData
    {
        public string formId { get; set; }
        public string original { get; set; }
        public string encryption { get; set; }
        public string extension { get; set; }
        public string newid { get; set; }
    }

    public class sItemModels
    {
        [Required]
        public List<Dictionary<string, object>> items { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class sItemsModels
    {
        [Required]
        public bool showItem { get; set; }
        [Required]
        public int itemCount { get; set; }
        [Required]
        public List<Dictionary<string, object>> items { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class iFormData
    {
        public string formId { get; set; }
        public string tile { get; set; }
        public List<Dictionary<string, object>> items { get; set; }
        public string newid { get; set; }
    }

    public class sFileData
    {
        public string imagePath { get; set; }
        public string original { get; set; }
        public string encryption { get; set; }
        public string extension { get; set; }
        public string newid { get; set; }
    }

    public class rFileData
    {
        public string imagePath { get; set; }
        public string original { get; set; }
        public string encryption { get; set; }
        public string extension { get; set; }
        public string first { get; set; }
        public string final { get; set; }
        public string newid { get; set; }
    }

    public class sDataModels
    {
        [Required]
        public string value { get; set; }
        [Required]
        public string status { get; set; }
    }

    //

    public class sArrayModels
    {
        [Required]
        public string[] items { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class sArItemModels
    {
        [Required]
        public List<Dictionary<string, object>> array { get; set; }
        [Required]
        public List<Dictionary<string, object>> items { get; set; }
        [Required]
        public string status { get; set; }
    }

    public class sDesoData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public string firdate { get; set; }
        public string secdate { get; set; }
        public string record { get; set; }
        public string value { get; set; }
        public string newid { get; set; }
    }

    public class sScroData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public string record { get; set; }
        public string value { get; set; }
        public string newid { get; set; }
    }

    public class sFidtData
    {
        public string firdate { get; set; }
        public string secdate { get; set; }
        public string record { get; set; }
        public string newid { get; set; }
    }

    public class sDeftData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public string firdate { get; set; }
        public string secdate { get; set; }
        public string record { get; set; }
        public int index { get; set; }
        public string value { get; set; }
        public string newid { get; set; }
    }

    public class sFiltData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public int index { get; set; }
        public string value { get; set; }
        public string record { get; set; }
        public string newid { get; set; }
    }

    /*public class sFtCoData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public string value { get; set; }
        public string newid { get; set; }
    }*/

    public class iFormsData
    {
        public string formId { get; set; }
        public string tile { get; set; }
        public List<Dictionary<string, object>> items { get; set; }
        public List<Dictionary<string, object>> qaitems { get; set; }
        public string newid { get; set; }
    }

    public class iSideData
    {
        public List<Dictionary<string, object>> items { get; set; }
        public List<Dictionary<string, object>> photoitems { get; set; }
        public List<Dictionary<string, object>> grotoitems { get; set; }
        public string newid { get; set; }
    }

    public class iSirmsData
    {
        public string formId { get; set; }
        public string tile { get; set; }
        public List<Dictionary<string, object>> items { get; set; }
        public List<Dictionary<string, object>> photoitems { get; set; }
        public List<Dictionary<string, object>> grotoitems { get; set; }
        public string newid { get; set; }
    }
}