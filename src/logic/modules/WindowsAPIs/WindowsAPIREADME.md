# OgYtScriptC++ WinAPI functions

<style>
    .content {
        display: none;
    }
</style>
<script>
    function Util(id) {
        const Content = document.getElementById(id);
        if (Content.style.display === 'block')
        {
            Content.style.display = 'none';
        }
        else
        {
            Content.style.display = 'block';
        }
    }
</script>

<button onclick="Util('content')"><span style="font-size: 16px;">`Registry`</span></button>
<div class="content" id="content">

<button onclick="Util('hkey_str')">`hKeyStr`</button>

<div id="hkey_str" class="content">
<div style="width: 200px;">

`HKEY_CLASSES_ROOT`<br>
`HKEY_CURRENT_USER`<br>
`HKEY_LOCAL_MACHINE`<br>
`HKEY_USERS`<br>
`HKEY_CURRENT_CONFIG`<br>

</div>
</div>

`RegOpenKeyExA( [hKey_str], [subkey_str], [sam_str], [var_name] )`<br>
`RegCreateKeyExA`<br>
`RegCloseKeyExA`<br>
`RegDeleteKeyExA`<br>
`RegSetValueExA`<br>
`RegQueryValueExA`<br>

</div>

<button onclick="Util('RAM')"><span style="font-size: 16px;">`RAM`</button>
<div id="RAM" class="content">

`GetGlobalMemoryInfo()`<br>
`GetMemoryUsageInfo()`<br>

</div>