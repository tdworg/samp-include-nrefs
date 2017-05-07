stock abc() {
	abc();
}

main()
{
	printf("%d", NRefs_GetNumRefs(addressofex(abc())));
}
