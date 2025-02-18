char firstNotRepeatingChar(string s)
{
unordered_map<char, int> order;
    for (int i =0; i < s.length(); i++)
    {
        char c = s[i];
        unordered_map<char, int>::iterator it = order.find(c);
        
        if (it != order.end())
        {
            it->second++; // we add all elements here and increment repeats
        }
        else
        {
            order.insert(make_pair(c,1));
            //order.insert({c,1});
        }
    }
    
    for (int i =0; i < s.length(); i++)
    {
        char c = s[i];
        unordered_map<char, int>::iterator it2 = order.find(c);
        if (it2->second == 1)
        {
            return c;
        }

    }
    
    return '_';
}
