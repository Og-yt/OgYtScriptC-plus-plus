# OgYtScriptC++

### Syntaxs

<style>
    .content {
        display: none;
    }
</style>
<script>
    function util(id) {
        const Content = document.getElementById(id);
        if (Content.style.display === 'block') {
            Content.style.display = 'none';
        } else {
            Content.style.display = 'block';
        }
    }
</script>

<button onclick="util('module')">`modules`</button>
<div id="module" class="content">

`import ( "Math" )`<br>
`import ( "programmer" )`<br>
`import ( "Mosquito" )`<br>
`import ( "vector" )`<br>
`import ( "string" )`<br>
`import ( "algorithm" )`<br>
`import ( "time" )`<br>
`import ( "system" )`<br>
`import ( "windows" )`<br>
`import ( "SQL" )`<br>
`import ( "HTML" )`<br>

</div>

<button onclick="util('keywords')">`keywords`</button>
<div id="keywords" class="content">

`int` `uint` `sint`<br>
`short` `ushort` `sshort`<br>
`long` `ulong` `slong`<br>
`long long` `ulong long` `slong long`<br>
`double` `long double` `float`<br>
`string` `char` `uchar` `wchar`<br>
`bool`<br>
`noexcept`

</div>

<button onclick="util('controls')">`controls`</button>
<div id="controls" class="content">

`if` `elif` `else`<br>
`for`<br>
`while` `do`<br>
`try` `catch`<br>
`switch` `case`<br>
`default` `continue` `break`<br>
`INFINITY`<br>

</div>

<button onclick="util('special')">`special`</button>
<div id="special" class="content">

<button onclick="util('math')">`import ( "math" )`</button>
<div id="math" class="content">

`MathSin` `MathCos` `MathTan` `MathSqrt` `MathPower` `MathIntegral`...etc<br>

</div>

<button onclick="util('programmer')">`import ( "programmer )`</button>
<div id="programmer" class="content">

`BIN OCT HEX <variable> = Integer;`

</div>

<button onclick="util('mosquito')">`import ( "Mosquito" )`</button>
<div id="mosquito" class="content">

`MosqSoundStart( [frequency], [duration] )`<br>
`MosqSoundStop()`

</div>

<button onclick="util('time')">`import ( "time" )`</button>
<div id="time" class="content">

`CurrentWorldTime( [CountryCode: Length 3] )`

</div>

<button onclick="util('system')">`import ( "system" )`</button>
<div id="system" class="content">

`OpenCommand( [CMD] | [DISKPART] )`

</div>

<button onclick="util('windows')">`import ( "windows" )`</button>
<div id="windows" class="content">

###### <a href="src/logic/modules/WindowsAPIs/WindowsAPIREADME.md"> windowsAPI README.md of reference </a>

</div>

</div>

###### ビルド不可能
###### windows関連の関数でシステムが不安定になる場合がございます。
###### 不明な点はソースコードを参照。今後、説明書を作成。 2026/08/29
