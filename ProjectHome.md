<h1>Text Oriented Universal Programming Language</h1>

Toupl is a super programming language, designed for text generation tasks. Syntax based on <a href='http://brother-john.net/tagz/'>Foobar 2000 Tagz Script</a>, but modified and extended for more power, symmetric, easy and generic. Currently supporting generation to:
  * <a href='http://en.wikipedia.org/wiki/C%2B%2B'>C++</a>
  * <a href='http://en.wikipedia.org/wiki/C_Sharp'>C#</a>
  * <a href='http://en.wikipedia.org/wiki/Java_(programming_language)'>Java</a>
  * <a href='http://en.wikipedia.org/wiki/JavaScript'><code>JavaScipt</code></a>
  * <a href='http://en.wikipedia.org/wiki/ECMAScript'>ECMAScript</a>
  * <a href='http://en.wikipedia.org/wiki/Lua_(programming_language)'>Lua</a>
  * <a href='http://en.wikipedia.org/wiki/PHP'>PHP</a>
  * <a href='http://en.wikipedia.org/wiki/Python_(programming_language)'>Python</a>
  * <a href='http://en.wikipedia.org/wiki/Visual_Basic'>Visual Basic</a>.

<h1> Syntax </h1>

Because language designed for text generation, text may be simply outputted as is.
```
Hello world!
```

Target language variable or expression can be outputted by enclosing in <b>%</b> <b>%</b> tags
```
Variable var0 is equivalent %var0%
1+2=%1+2%
```

Target language code can be included by enclosing in <b>?%</b> <b>%?</b> tags
```
?%
  int i;
  int n=100;
  
  while(i<n)
  {
%?%i*i% ?%
    ++i;
  }
%?
```

Native condition output supported
```
?%
var _genImage=function(src,alt,width,height)
{
%?
<img [% src=&%src%&%][% alt=&%alt%&%][% width="&%width%&"%][% height="&%height%&"%]>
?%
  return fpText;
}
%?
```
Conditional text putted between <b><code>[%</code></b> <b><code>%]</code></b>  tags and will be outputted if all condition variables inside not null.
Conditional variables same as ordinary variables but enclosing by <b>&%</b> <b>%&</b> instead <b>%</b> <b>%</b>.

There is a comments
```
/%
  block comment
%/
//% line comment  
```

In situation, when you need output text, that contains elements\tags of toupl,you can enclose this in special ignore tags <b>!%</b> <b>%!</b>
```
!% all /% this % text ?% outputted  %] %!
!% even !% you can output %!
!% if you want to output %!%! -  simply twice is %!
```

<h1>Technical details</h1>
Depends from target language text outputted as append operation to <b>String fpText</b> or to <b><code>StringBuilder fpStringBuilder</code></b> (Java and Visual Basic cases). In case of C++ language you can specify work <b>String</b> class (default - <b>std::string</b>).
In native condition construction variables tested with bool <b><code>_fpT(String)</code></b> function. You must code it.

Command line options
<pre>
Usage toupl {param:value|"param:value_with_whitespaces"}<br>
Params:<br>
-infile		Input file<br>
-outfile	Output file or "auto"(cut .toupl extension) else stdout<br>
-lang		Input file language or auto (by extension)<br>
List of supported languages:<br>
|| *name* || *-lang option* ||<br>
|| {{{JavaScript}}} || javascript ||<br>
|| C++ || cpp ||<br>
|| Java || java ||<br>
|| C# || csharp ||<br>
|| Python || python ||<br>
|| PHP || php ||<br>
|| Lua || lua ||<br>
|| {{{Visual Basic}}} || vb ||<br>
C++ Params<br>
-stringclassname		Work string class or std::string<br>
Python Params<br>
-indent		{s|t}count,s=space,t=tabs<br>
</pre>

<h1>Code generation examples</h1>
<h2>Full syntax test</h2>
Other tests you can find <a href='http://code.google.com/p/toupl/source/browse/#svn/trunk/test'>here</a>
```
/% minimal test %/
?%
int i;
int n=100;
while(i<n)
{
%?[%arr!%[%!%i%!%]%!=&%arr[i]%&%]
?%
}
%?
//% end of minimal test
```
<h2>C++</h2>
```
fpText+="\n";

int i;
int n=100;
while(i<n)
{
bool fpVar55;
std::string fpVar74;
fpVar55=(fpVar74=arr[i],_fpT(fpVar74));
if(fpVar55)
{
fpText+="arr";
fpText+="[";
fpText+=i;
fpText+="]";
fpText+="=";
fpText+=fpVar74;
}
fpText+="\n";

}
fpText+="\n";
```
<h2>Java</h2>
```
fpStringBuilder.append("\n");

int i;
int n=100;
while(i<n)
{
boolean fpVar55;
String fpVar74;
fpVar55=(fpVar74=arr[i],_fpT(fpVar74));
if(fpVar55)
{
fpStringBuilder.append("arr");
fpStringBuilder.append("[");
fpStringBuilder.append(i);
fpStringBuilder.append("]");
fpStringBuilder.append("=");
fpStringBuilder.append(fpVar74);
}
fpStringBuilder.append("\n");

}
fpStringBuilder.append("\n");
```
<h2>C#</h2>
```
fpText+="\n";

int i;
int n=100;
while(i<n)
{
Boolean fpVar55;
String fpVar74;
fpVar55=(fpVar74=arr[i],_fpT(fpVar74));
if(fpVar55)
{
fpText+="arr";
fpText+="[";
fpText+=i;
fpText+="]";
fpText+="=";
fpText+=fpVar74;
}
fpText+="\n";

}
fpText+="\n";
```
<h2><code>JavaScript</code></h2>
```
fpText+="\n";

int i;
int n=100;
while(i<n)
{
var fpVar55;
var fpVar74;
fpVar55=(fpVar74=arr[i],_fpT(fpVar74));
if(fpVar55)
{
fpText+="arr";
fpText+="[";
fpText+=i;
fpText+="]";
fpText+="=";
fpText+=fpVar74;
}
fpText+="\n";

}
fpText+="\n";
```
<h2>Python</h2>
```
fpText+='\n'

int i;
int n=100;
while(i<n)
{
fpVar55=(fpVar74=arr[i],_fpT(fpVar74))[1]
if fpVar55:
  fpText+='arr'
  fpText+='['
  fpText+=i
  fpText+=']'
  fpText+='='
  fpText+=fpVar74
fpText+='\n'

}
fpText+='\n'
```
<h2>PHP</h2>
```
int i;
int n=100;
while(i<n)
{
<?php $fpVar55=($fpVar74=$arr[i],_fpT($fpVar74))?><?php if($fpVar55)
{
?>arr[<?php echo $i?>
]=<?php echo $fpVar74?>
<?php } ?>

}
```
<h2>Lua</h2>
```
fpText=fpText.."\n";

int i;
int n=100;
while(i<n)
{
local fpVar55;
local fpVar74;
fpVar55=(function () fpVar74=arr[i]; return _fpT(fpVar74); end)();
if fpVar55 then
fpText=fpText.."arr";
fpText=fpText.."[";
fpText=fpText..i;
fpText=fpText.."]";
fpText=fpText.."=";
fpText=fpText..fpVar74;
end
fpText=fpText.."\n";

}
fpText=fpText.."\n";
```
<h2>Visual Basic</h2>
```
fpStringBuilder.Append("" & VbCrLf & "")

int i;
int n=100;
while(i<n)
{
Dim fpVar55 As Boolean 
Dim fpVar74 As String 
Do
'fpVBLoop
fpVar74=arr[i]
If NOT _fpT(fpVar74) Then Exit Do
fpVar55=True
Loop Until True
If fpVar55 Then
fpStringBuilder.Append("arr")
fpStringBuilder.Append("[")
fpStringBuilder.Append(i)
fpStringBuilder.Append("]")
fpStringBuilder.Append("=")
fpStringBuilder.Append(fpVar74)
End If
fpStringBuilder.Append("" & VbCrLf & "")

}
fpStringBuilder.Append("" & VbCrLf & "")
```