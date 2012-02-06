#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main() {


std::string str = "<div id=\"tyda_message\"></div><div id=\"R14\"><table cellpadding=\"0\" cellspacing=\"0\" class=\"tyda_entry\"><tr><td class=\"tyda_entry_word\"><span class=\"tyda_entry_base\">hej</span></td><td class=\"tyda_entry_edit\"><a class=\"tyda_action\" href=\"/word-discuss?lang=sv&amp;string=hej\" title=\"Diskutera ordet &quot;hej&quot; (22 inlägg)\">Diskutera(22)</a><a class=\"tyda_action\" href=\"/word-bug?word=1402312\" title=\"Lämna förslag på ändring\">Ändra</a></td></tr></table><table class=\"tyda_res\"><tr><td><table cellpadding=\"0\" cellspacing=\"0\" class=\"tyda_res_header\"><tr><td class=\"tyda_res_header_l\"></td><td class=\"tyda_res_header_wc\"><table cellpadding=\"0\" cellspacing=\"0\"><tr><td><img title=\"svenskt uppslagsord\" src=\"/images/flag_sv.png\" alt=\"\" width=\"17\" height=\"11\"/></td><td title=\"Ordklass för 'hej'\">interjektion </td></tr></table></td><td class=\"tyda_res_header_trans\"><table cellpadding=\"0\" cellspacing=\"0\"><tr><td><img title=\"engelsk översättning\" src=\"/images/flag_en.png\" alt=\"\" width=\"17\" height=\"11\"/></td><td title=\"Översättning av 'hej'\">översättning</td></tr></table></td><td class=\"tyda_res_header_r\"></td></tr></table></td></tr><tr><td><table cellpadding=\"0\" cellspacing=\"0\" class=\"tyda_res_body\"><tbody id=\"R3\"><tr><td class=\"tyda_res_body_wc_no_top_border\"><table id=\"R4\" class=\"tyda_res_body_wc\" cellpadding=\"0\" cellspacing=\"0\"><tr><td class=\"tyda_expander\"><div class=\"tyda_expander\"><a class=\"tyda_expander_button\" onclick=\"replace_id('R4','/interface/call?c=display_sense_td_left%2CR4%2C1402312%2C895220%2C1%2CALL%2C1%2CS%253AN%253B%2C0');expander_register_status('R4',1);ads_reload();return false;\" href=\"#\"><img class=\"tyda_expander_button\" src=\"/images/data_plus.png\" alt=\"Visa detaljer\" title=\"Visa detaljer\"/></a></div></td><td class=\"tyda_meaning_syn_no_border_top\"><div><a href=\"/search/hall%C3%A5\">hallå</a>, <a href=\"/search/tja\">tja</a><span class=\"tyda_assoc_sense_mark\"> [vanliga uttryck]</span>, <a href=\"/search/goddag\">goddag</a>, <a href=\"/search/hejsan\">hejsan</a>, <a href=\"/search/halloj\">halloj</a></div></td></tr></table></td><td class=\"tyda_res_body_trans_no_top_border\"><div id=\"R5\"><table class=\"tyda_res_body_trans\" cellpadding=\"0\" cellspacing=\"0\"><tr><td class=\"tyda_no_padding_top\"><a id=\"tyda_transR6\" href=\"/search/hi\">hi</a> </td><td class=\"tyda_trans_actions tyda_no_padding_top\"><div title=\"header=[] body=[Klicka för att lyssna!&lt;br/&gt;Uttalas: &lt;span class='tyda_ipa'&gt;haɪ&lt;/span&gt;&lt;/div&gt;] offsetx=[-195] offsety=[10]\" class=\"word_tool_box\" ><a href=\"#\" onclick=\"MakeRequest2('hi', 'en'); return false;\"><img alt=\"\" border=\"0\" width=\"19\" height=\"15\" src=\"/images/speaker.png\" /></a></div> <a rel=\"nofollow\" href=\"http://www.macmillandictionary.com/search/british/?q=hi\"><img src=\"/images/macmillan.png\" alt=\"macmillan\" title=\"Further information from www.macmillandictionary.com\"/></a><div title=\"header=[] body=[&lt;div class='tyda_tooltip_text'&gt;Klicka för att kopiera&lt;/div&gt;] offsetx=[-195] offsety=[10]\" class=\"word_tool_box\" ><a href=\"#\" onclick=\"copyToClipboard(document.getElementById('tyda_transR6').innerHTML); return false;\"><img alt=\"\" border=\"0\" width=\"13\" height=\"15\" src=\"/images/copy.png\" /></a></div></td></tr><tr><td class=\"\"><a id=\"tyda_transR7\" href=\"/search/hey\">hey</a> </td><td class=\"tyda_trans_actions \"><div title=\"header=[] body=[Klicka för att lyssna!&lt;br/&gt;Uttalas: &lt;span class='tyda_ipa'&gt;heɪ&lt;/span&gt;&lt;/div&gt;] offsetx=[-195] offsety=[10]\" class=\"word_tool_box\" ><a href=\"#\" onclick=\"MakeRequest2('hey', 'en'); return false;\"><img alt=\"\" border=\"0\" width=\"19\" height=\"15\" src=\"/images/speaker.png\" /></a></div> <a rel=\"nofollow\" href=\"http://www.macmillandictionary.com/search/british/?q=hey\"><img src=\"/images/macmillan.png\" alt=\"macmillan\" title=\"Further information from www.macmillandictionary.com\"/></a><div title=\"header=[] body=[&lt;div class='tyda_tooltip_text'&gt;Klicka för att kopiera&lt;/div&gt;] offsetx=[-195] offsety=[10]\" class=\"word_tool_box\" ><a href=\"#\" onclick=\"copyToClipboard(document.getElementById('tyda_transR7').innerHTML); return false;\"><img alt=\"\" border=\"0\" width=\"13\" height=\"15\" src=\"/images/copy.png\" /></a></div></td></tr>";



    //<a id="tyda_transR7" href="/search/hey">hey</a>
    //const boost::regex exp("<a id=\"(tyda_transR[^\"]*)\" href=\"[^\"]*\">([^<]*)");

    //<a href="/search/goddag">goddag</a>
    //const boost::regex exp("<a href=\"\\/(search)\\/[^\"]*\">([^<]*)");

    const boost::regex exp("<a (id=\"tyda_transR|href=\"\\/search\\/)[^\"]*\"[^>]*>([^<]*)<");

    int const subs[] = {1, 2};
    boost::sregex_token_iterator itr(str.begin(), str.end(), exp, subs);
    boost::sregex_token_iterator end;

    for (;itr != end; ++itr){
        //std::string tmp(itr->first, itr->second);
        //std::cout << " [ " << tmp << " ]" << std::endl;

        std::cout << " [ " << *itr  << " ] "  << std::endl;

    }

    return 0;
}
