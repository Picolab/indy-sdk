#!/bin/bash
rm -rf docs
typedoc --out docs --mode modules --includeDeclarations --excludeExternals --entryPoint LibIndy --ignoreCompilerErrors src
