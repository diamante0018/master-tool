libtommath = {
	source = path.join(dependencies.basePath, "libtommath"),
}

function libtommath.import()
	links {
		"libtommath"
	}

	libtommath.includes()
end

function libtommath.includes()
	includedirs {
		libtommath.source
	}

	if os.istarget("windows") then
		defines {
			"MP_NO_DEV_URANDOM",
		}
	end

	defines {
		"LTM_DESC",
		"__STDC_IEC_559__",
	}
end

function libtommath.project()
	project "libtommath"
		language "C"

		libtommath.includes()

		files {
			path.join(libtommath.source, "*.c"),
		}

		defines {
			"_LIB"
		}

		removedefines {
			"_DLL",
			"_USRDLL"
		}

		if os.istarget("darwin") then
			filter "platforms:arm64"
				buildoptions {
					"-arch arm64"
				}
			filter {}
		end

		warnings "Off"
		kind "StaticLib"
end

table.insert(dependencies, libtommath)
