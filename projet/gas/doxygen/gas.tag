<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>gas.h</name>
    <path>/home/anthony973/Git/Git_Projects/INF1995/projet/gas/</path>
    <filename>gas_8h</filename>
    <class kind="class">GAS</class>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>Opcode</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a8915a9fcfa3b7654398da037346cf7b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::string</type>
      <name>HELP</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a44bc41b3869f7d1b6eb3f1e052befcdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::string</type>
      <name>EMAIL</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>affb753c0ffda6424fbac18615717cfc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::string</type>
      <name>INI</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a3f668e597fe186053850141349c45ef8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::string</type>
      <name>TNL</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>afc94044097fefa2cd4194b23d6f37615</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::string</type>
      <name>TNR</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a9d1fbecef7fda5fb1cf35564b46544a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::string</type>
      <name>MDL</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a978d597cd7ae51efed145521847a984a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::string</type>
      <name>ENP</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a93c73b79818ce7cac490249b801edfc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const Opcode</type>
      <name>INI_OP</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a590a0c11f2b91ddbc19cacdf953de64f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const Opcode</type>
      <name>TNL_OP</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a0e6112ec6c50f8abca9b246e8fbd6a5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const Opcode</type>
      <name>TNR_OP</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>a9c438c770dbad5409b289b571836df60</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const Opcode</type>
      <name>MDL_OP</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>ac5864be7341f9dfdcac1ce7aac4d5465</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const Opcode</type>
      <name>ENP_OP</name>
      <anchorfile>gas_8h.html</anchorfile>
      <anchor>aa89a4eee484858e85e29a2eae74ab339</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GAS</name>
    <filename>classGAS.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>run</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a235c7235123998b16f3bb2eafd0d004b</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static bool</type>
      <name>_shouldCompile</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>af978924b1caa6184b98660a1537a98a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_compile</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a0b7d40f0a4d47c13ec3f7ee93ed6581d</anchor>
      <arglist>(const std::string &amp;ifName, const std::string &amp;ofName)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_openInputFile</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>afe6a851ddf807c767b9d502e8720128d</anchor>
      <arglist>(const std::string &amp;ifName)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_closeFiles</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a0d5b928d439765230c5dc5710735c1f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_startOver</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a448c9c2e636992cb5daf185d73a63dea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_compileInputFile</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a04b8aa271adefeb768254b8f7ffb3d2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_emitCodeFromToken</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a1539805e1f0cc5a6c0ad40d9b27299d5</anchor>
      <arglist>(std::string token)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_addHeader</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a576756efb5fd67dde735c9dbb7d46383</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_flushIntoOutputFile</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a10785f0fa430cda54dc1f92f1f35cc2f</anchor>
      <arglist>(const std::string &amp;ofName)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_printHelp</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a2e86697c4b098e07ff3ea18bddd0f140</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>_sendEmail</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>ab3e75efe5203a038b7db8cef1175740d</anchor>
      <arglist>(const std::string &amp;email)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static std::list&lt; unsigned char &gt;</type>
      <name>_instrs</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a13ac1eaf5d3e7383efe300e3b4bc8dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static std::list&lt; unsigned short &gt;</type>
      <name>_pathAddr</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a48b918106503e6ef38c8f8f801cbb14d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static std::ifstream</type>
      <name>_iFile</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>ae89cc1d8cbd56526f10a4c4caf6803d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static std::ofstream</type>
      <name>_oFile</name>
      <anchorfile>classGAS.html</anchorfile>
      <anchor>a70a485daa82cf239fe887b51b89c66e2</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
