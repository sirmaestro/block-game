import sys, re, pefile

pe = pefile.PE(sys.argv[1])
oh = pe.OPTIONAL_HEADER
print(f"ImageBase {oh.ImageBase:#x} EntryPoint {oh.AddressOfEntryPoint + oh.ImageBase:#x} Linker {oh.MajorLinkerVersion}.{oh.MinorLinkerVersion} Subsystem {oh.Subsystem}")
print("\n== sections")
for s in pe.sections:
    print(f"{s.Name.rstrip(b'\0').decode():8} va={s.VirtualAddress + oh.ImageBase:#x} vsize={s.Misc_VirtualSize:#x} raw={s.SizeOfRawData:#x} chars={s.Characteristics:#x}")

print("\n== imports")
for d in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
    names = [f"{(i.name or b'#%d' % i.ordinal).decode()}@{i.address:#x}" for i in d.imports]
    print(d.dll.decode(), len(names))
    print("   " + ", ".join(names))

print("\n== resources")
if hasattr(pe, "DIRECTORY_ENTRY_RESOURCE"):
    for t in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        tname = str(t.name) if t.name else pefile.RESOURCE_TYPE.get(t.id, t.id)
        for n in t.directory.entries:
            nname = str(n.name) if n.name else n.id
            for l in n.directory.entries:
                print(f"  {tname} {nname} lang={l.id} size={l.data.struct.Size} rva={l.data.struct.OffsetToData:#x}")

print("\n== strings (ascii >= 5)")
data = open(sys.argv[1], "rb").read()
for m in re.finditer(rb"[\x20-\x7e]{5,}", data):
    print(f"{m.start():#08x} {m.group().decode()}")
