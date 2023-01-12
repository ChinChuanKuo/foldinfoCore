namespace FOLDINFOCore.App_Code
{
    public class information
    {
        public string osystem(string userAgent)
        {
            switch (userAgent.IndexOf("Android"))
            {
                case -1:
                    switch (userAgent.IndexOf("iPhone"))
                    {
                        case -1:
                            switch (userAgent.IndexOf("Mac OS X"))
                            {
                                case -1:
                                    switch (userAgent.IndexOf("Windows"))
                                    {
                                        case -1:
                                            switch (userAgent.IndexOf("Linux"))
                                            {
                                                case -1:
                                                    return "Others";
                                                default:
                                                    return "Linux";
                                            }
                                        default:
                                            return "Windows";
                                    }
                                default:
                                    return "Mac OS X";
                            }
                        default:
                            return "IOS";
                    }
                default:
                    return "Android";
            }
        }

        public string browser(string userAgent)
        {
            switch (userAgent.IndexOf("Safari"))
            {
                case -1:
                    switch (userAgent.IndexOf("Trident"))
                    {
                        case -1:
                            switch (userAgent.IndexOf("Edge"))
                            {
                                case -1:
                                    return "FireFox";
                                default:
                                    return "IeEdge";
                            }
                        default:
                            return "IeEdge";
                    }
                default:
                    return "Safari/Google";
            }
        }
    }
}