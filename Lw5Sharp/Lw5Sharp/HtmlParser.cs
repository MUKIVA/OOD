using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Document
{
    static class HtmlParser
    {
        private static Dictionary<char, string> _htmlEntities = new Dictionary<char, string>() 
        {
            { '<',   "&lt;" },
            { '>',   "&gt;" },
            { '"',   "&quot;" },
            { '\'',  "&apos;" },
            { '&',   "&amp;" }
        };

        public static string ParseHtmlString(string text)
        {
            Regex regex = new Regex("[<>\"'&]", RegexOptions.RightToLeft);
            MatchCollection matchCollection = regex.Matches(text);

            if (matchCollection.Count == 0)
                return text;

            StringBuilder builder = new StringBuilder(text);

            foreach (Match match in matchCollection)
            {
                builder.Replace(
                    builder[match.Index].ToString(), 
                    _htmlEntities[builder[match.Index]],
                    match.Index, 1
                );
            }

            return builder.ToString();    
        }


    }
}
