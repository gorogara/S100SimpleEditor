#pragma once
#include <string>

namespace S100
{       

	enum S100_DataProduct
	{
		S_101TDS = 1001,
		S_100 = 100 ,
		S_101 = 101	,
		S_102 = 102	,
		S_103 = 103	,
		S_104 = 104	,
		S_105 = 105	,
		S_106 = 106	,
		S_107 = 107	,
		S_108 = 108	,
		S_109 = 109	,
		S_110 = 110	,
		S_111 = 111	,
		S_112 = 112	,
		S_113 = 113	,
		S_114 = 114	,
		S_115 = 115	,
		S_116 = 116	,
		S_117 = 117	,
		S_118 = 118	,
		S_119 = 119	,
		S_120 = 120	,
		S_121 = 121	,
		S_122 = 122	,
		S_123 = 123	,
		S_124 = 124	,
		S_125 = 125	,
		S_126 = 126	,
		S_127 = 127	,
		S_128 = 128	,
		S_129 = 129	,
		S_130 = 130	,
		S_131 = 131	,
		S_132 = 132	,
		S_133 = 133	,
		S_134 = 134	,
		S_135 = 135	,
		S_136 = 136	,
		S_137 = 137	,
		S_138 = 138	,
		S_139 = 139	,
		S_140 = 140	,
		S_141 = 141	,
		S_142 = 142	,
		S_143 = 143	,
		S_144 = 144	,
		S_145 = 145	,
		S_146 = 146	,
		S_147 = 147	,
		S_148 = 148	,
		S_149 = 149	,
		S_150 = 150	,
		S_151 = 151	,
		S_152 = 152	,
		S_153 = 153	,
		S_154 = 154	,
		S_155 = 155	,
		S_156 = 156	,
		S_157 = 157	,
		S_158 = 158	,
		S_159 = 159	,
		S_160 = 160	,
		S_161 = 161	,
		S_162 = 162	,
		S_163 = 163	,
		S_164 = 164	,
		S_165 = 165	,
		S_166 = 166	,
		S_167 = 167	,
		S_168 = 168	,
		S_169 = 169	,
		S_170 = 170	,
		S_171 = 171	,
		S_172 = 172	,
		S_173 = 173	,
		S_174 = 174	,
		S_175 = 175	,
		S_176 = 176	,
		S_177 = 177	,
		S_178 = 178	,
		S_179 = 179	,
		S_180 = 180	,
		S_181 = 181	,
		S_182 = 182	,
		S_183 = 183	,
		S_184 = 184	,
		S_185 = 185	,
		S_186 = 186	,
		S_187 = 187	,
		S_188 = 188	,
		S_189 = 189	,
		S_190 = 190	,
		S_191 = 191	,
		S_192 = 192	,
		S_193 = 193	,
		S_194 = 194	,
		S_195 = 195	,
		S_196 = 196	,
		S_197 = 197	,
		S_198 = 198	,
		S_199 = 199	,
		S_200 = 200	,
		S_201 = 201	,
		S_202 = 202	,
		S_203 = 203	,
		S_204 = 204	,
		S_205 = 205	,
		S_206 = 206	,
		S_207 = 207	,
		S_208 = 208	,
		S_209 = 209	,
		S_210 = 210	,
		S_211 = 211	,
		S_212 = 212	,
		S_213 = 213	,
		S_214 = 214	,
		S_215 = 215	,
		S_216 = 216	,
		S_217 = 217	,
		S_218 = 218	,
		S_219 = 219	,
		S_220 = 220	,
		S_221 = 221	,
		S_222 = 222	,
		S_223 = 223	,
		S_224 = 224	,
		S_225 = 225	,
		S_226 = 226	,
		S_227 = 227	,
		S_228 = 228	,
		S_229 = 229	,
		S_230 = 230	,
		S_231 = 231	,
		S_232 = 232	,
		S_233 = 233	,
		S_234 = 234	,
		S_235 = 235	,
		S_236 = 236	,
		S_237 = 237	,
		S_238 = 238	,
		S_239 = 239	,
		S_240 = 240	,
		S_241 = 241	,
		S_242 = 242	,
		S_243 = 243	,
		S_244 = 244	,
		S_245 = 245	,
		S_246 = 246	,
		S_247 = 247	,
		S_248 = 248	,
		S_249 = 249	,
		S_250 = 250	,
		S_251 = 251	,
		S_252 = 252	,
		S_253 = 253	,
		S_254 = 254	,
		S_255 = 255	,
		S_256 = 256	,
		S_257 = 257	,
		S_258 = 258	,
		S_259 = 259	,
		S_260 = 260	,
		S_261 = 261	,
		S_262 = 262	,
		S_263 = 263	,
		S_264 = 264	,
		S_265 = 265	,
		S_266 = 266	,
		S_267 = 267	,
		S_268 = 268	,
		S_269 = 269	,
		S_270 = 270	,
		S_271 = 271	,
		S_272 = 272	,
		S_273 = 273	,
		S_274 = 274	,
		S_275 = 275	,
		S_276 = 276	,
		S_277 = 277	,
		S_278 = 278	,
		S_279 = 279	,
		S_280 = 280	,
		S_281 = 281	,
		S_282 = 282	,
		S_283 = 283	,
		S_284 = 284	,
		S_285 = 285	,
		S_286 = 286	,
		S_287 = 287	,
		S_288 = 288	,
		S_289 = 289	,
		S_290 = 290	,
		S_291 = 291	,
		S_292 = 292	,
		S_293 = 293	,
		S_294 = 294	,
		S_295 = 295	,
		S_296 = 296	,
		S_297 = 297	,
		S_298 = 298	,
		S_299 = 299	,
		S_300 = 300	,
		S_301 = 301	,
		S_302 = 302	,
		S_303 = 303	,
		S_304 = 304	,
		S_305 = 305	,
		S_306 = 306	,
		S_307 = 307	,
		S_308 = 308	,
		S_309 = 309	,
		S_310 = 310	,
		S_311 = 311	,
		S_312 = 312	,
		S_313 = 313	,
		S_314 = 314	,
		S_315 = 315	,
		S_316 = 316	,
		S_317 = 317	,
		S_318 = 318	,
		S_319 = 319	,
		S_320 = 320	,
		S_321 = 321	,
		S_322 = 322	,
		S_323 = 323	,
		S_324 = 324	,
		S_325 = 325	,
		S_326 = 326	,
		S_327 = 327	,
		S_328 = 328	,
		S_329 = 329	,
		S_330 = 330	,
		S_331 = 331	,
		S_332 = 332	,
		S_333 = 333	,
		S_334 = 334	,
		S_335 = 335	,
		S_336 = 336	,
		S_337 = 337	,
		S_338 = 338	,
		S_339 = 339	,
		S_340 = 340	,
		S_341 = 341	,
		S_342 = 342	,
		S_343 = 343	,
		S_344 = 344	,
		S_345 = 345	,
		S_346 = 346	,
		S_347 = 347	,
		S_348 = 348	,
		S_349 = 349	,
		S_350 = 350	,
		S_351 = 351	,
		S_352 = 352	,
		S_353 = 353	,
		S_354 = 354	,
		S_355 = 355	,
		S_356 = 356	,
		S_357 = 357	,
		S_358 = 358	,
		S_359 = 359	,
		S_360 = 360	,
		S_361 = 361	,
		S_362 = 362	,
		S_363 = 363	,
		S_364 = 364	,
		S_365 = 365	,
		S_366 = 366	,
		S_367 = 367	,
		S_368 = 368	,
		S_369 = 369	,
		S_370 = 370	,
		S_371 = 371	,
		S_372 = 372	,
		S_373 = 373	,
		S_374 = 374	,
		S_375 = 375	,
		S_376 = 376	,
		S_377 = 377	,
		S_378 = 378	,
		S_379 = 379	,
		S_380 = 380	,
		S_381 = 381	,
		S_382 = 382	,
		S_383 = 383	,
		S_384 = 384	,
		S_385 = 385	,
		S_386 = 386	,
		S_387 = 387	,
		S_388 = 388	,
		S_389 = 389	,
		S_390 = 390	,
		S_391 = 391	,
		S_392 = 392	,
		S_393 = 393	,
		S_394 = 394	,
		S_395 = 395	,
		S_396 = 396	,
		S_397 = 397	,
		S_398 = 398	,
		S_399 = 399	,
		S_400 = 400	,
		S_401 = 401	,
		S_402 = 402	,
		S_403 = 403	,
		S_404 = 404	,
		S_405 = 405	,
		S_406 = 406	,
		S_407 = 407	,
		S_408 = 408	,
		S_409 = 409	,
		S_410 = 410	,
		S_411 = 411	,
		S_412 = 412	,
		S_413 = 413	,
		S_414 = 414	,
		S_415 = 415	,
		S_416 = 416	,
		S_417 = 417	,
		S_418 = 418	,
		S_419 = 419	,
		S_420 = 420	,
		S_421 = 421	,
		S_422 = 422	,
		S_423 = 423	,
		S_424 = 424	,
		S_425 = 425	,
		S_426 = 426	,
		S_427 = 427	,
		S_428 = 428	,
		S_429 = 429	,
		S_430 = 430	,
		S_431 = 431	,
		S_432 = 432	,
		S_433 = 433	,
		S_434 = 434	,
		S_435 = 435	,
		S_436 = 436	,
		S_437 = 437	,
		S_438 = 438	,
		S_439 = 439	,
		S_440 = 440	,
		S_441 = 441	,
		S_442 = 442	,
		S_443 = 443	,
		S_444 = 444	,
		S_445 = 445	,
		S_446 = 446	,
		S_447 = 447	,
		S_448 = 448	,
		S_449 = 449	,
		S_450 = 450	,
		S_451 = 451	,
		S_452 = 452	,
		S_453 = 453	,
		S_454 = 454	,
		S_455 = 455	,
		S_456 = 456	,
		S_457 = 457	,
		S_458 = 458	,
		S_459 = 459	,
		S_460 = 460	,
		S_461 = 461	,
		S_462 = 462	,
		S_463 = 463	,
		S_464 = 464	,
		S_465 = 465	,
		S_466 = 466	,
		S_467 = 467	,
		S_468 = 468	,
		S_469 = 469	,
		S_470 = 470	,
		S_471 = 471	,
		S_472 = 472	,
		S_473 = 473	,
		S_474 = 474	,
		S_475 = 475	,
		S_476 = 476	,
		S_477 = 477	,
		S_478 = 478	,
		S_479 = 479	,
		S_480 = 480	,
		S_481 = 481	,
		S_482 = 482	,
		S_483 = 483	,
		S_484 = 484	,
		S_485 = 485	,
		S_486 = 486	,
		S_487 = 487	,
		S_488 = 488	,
		S_489 = 489	,
		S_490 = 490	,
		S_491 = 491	,
		S_492 = 492	,
		S_493 = 493	,
		S_494 = 494	,
		S_495 = 495	,
		S_496 = 496	,
		S_497 = 497	,
		S_498 = 498	,
		S_499 = 499	,
		S_500 = 500	,
		S_501 = 501	,
		S_502 = 502	,
		S_503 = 503	,
		S_504 = 504	,
		S_505 = 505	,
		S_506 = 506	,
		S_507 = 507	,
		S_508 = 508	,
		S_509 = 509	,
		S_510 = 510	,
		S_511 = 511	,
		S_512 = 512	,
		S_513 = 513	,
		S_514 = 514	,
		S_515 = 515	,
		S_516 = 516	,
		S_517 = 517	,
		S_518 = 518	,
		S_519 = 519	,
		S_520 = 520	,
		S_521 = 521	,
		S_522 = 522	,
		S_523 = 523	,
		S_524 = 524	,
		S_525 = 525	,
		S_526 = 526	,
		S_527 = 527	,
		S_528 = 528	,
		S_529 = 529	,
		S_530 = 530	,
		S_531 = 531	,
		S_532 = 532	,
		S_533 = 533	,
		S_534 = 534	,
		S_535 = 535	,
		S_536 = 536	,
		S_537 = 537	,
		S_538 = 538	,
		S_539 = 539	,
		S_540 = 540	,
		S_541 = 541	,
		S_542 = 542	,
		S_543 = 543	,
		S_544 = 544	,
		S_545 = 545	,
		S_546 = 546	,
		S_547 = 547	,
		S_548 = 548	,
		S_549 = 549	,
		S_550 = 550	,
		S_551 = 551	,
		S_552 = 552	,
		S_553 = 553	,
		S_554 = 554	,
		S_555 = 555	,
		S_556 = 556	,
		S_557 = 557	,
		S_558 = 558	,
		S_559 = 559	,
		S_560 = 560	,
		S_561 = 561	,
		S_562 = 562	,
		S_563 = 563	,
		S_564 = 564	,
		S_565 = 565	,
		S_566 = 566	,
		S_567 = 567	,
		S_568 = 568	,
		S_569 = 569	,
		S_570 = 570	,
		S_571 = 571	,
		S_572 = 572	,
		S_573 = 573	,
		S_574 = 574	,
		S_575 = 575	,
		S_576 = 576	,
		S_577 = 577	,
		S_578 = 578	,
		S_579 = 579	,
		S_580 = 580	,
		S_581 = 581	,
		S_582 = 582	,
		S_583 = 583	,
		S_584 = 584	,
		S_585 = 585	,
		S_586 = 586	,
		S_587 = 587	,
		S_588 = 588	,
		S_589 = 589	,
		S_590 = 590	,
		S_591 = 591	,
		S_592 = 592	,
		S_593 = 593	,
		S_594 = 594	,
		S_595 = 595	,
		S_596 = 596	,
		S_597 = 597	,
		S_598 = 598	,
		S_599 = 599	,
		S_600 = 600	,
		S_601 = 601	,
		S_602 = 602	,
		S_603 = 603	,
		S_604 = 604	,
		S_605 = 605	,
		S_606 = 606	,
		S_607 = 607	,
		S_608 = 608	,
		S_609 = 609	,
		S_610 = 610	,
		S_611 = 611	,
		S_612 = 612	,
		S_613 = 613	,
		S_614 = 614	,
		S_615 = 615	,
		S_616 = 616	,
		S_617 = 617	,
		S_618 = 618	,
		S_619 = 619	,
		S_620 = 620	,
		S_621 = 621	,
		S_622 = 622	,
		S_623 = 623	,
		S_624 = 624	,
		S_625 = 625	,
		S_626 = 626	,
		S_627 = 627	,
		S_628 = 628	,
		S_629 = 629	,
		S_630 = 630	,
		S_631 = 631	,
		S_632 = 632	,
		S_633 = 633	,
		S_634 = 634	,
		S_635 = 635	,
		S_636 = 636	,
		S_637 = 637	,
		S_638 = 638	,
		S_639 = 639	,
		S_640 = 640	,
		S_641 = 641	,
		S_642 = 642	,
		S_643 = 643	,
		S_644 = 644	,
		S_645 = 645	,
		S_646 = 646	,
		S_647 = 647	,
		S_648 = 648	,
		S_649 = 649	,
		S_650 = 650	,
		S_651 = 651	,
		S_652 = 652	,
		S_653 = 653	,
		S_654 = 654	,
		S_655 = 655	,
		S_656 = 656	,
		S_657 = 657	,
		S_658 = 658	,
		S_659 = 659	,
		S_660 = 660	,
		S_661 = 661	,
		S_662 = 662	,
		S_663 = 663	,
		S_664 = 664	,
		S_665 = 665	,
		S_666 = 666	,
		S_667 = 667	,
		S_668 = 668	,
		S_669 = 669	,
		S_670 = 670	,
		S_671 = 671	,
		S_672 = 672	,
		S_673 = 673	,
		S_674 = 674	,
		S_675 = 675	,
		S_676 = 676	,
		S_677 = 677	,
		S_678 = 678	,
		S_679 = 679	,
		S_680 = 680	,
		S_681 = 681	,
		S_682 = 682	,
		S_683 = 683	,
		S_684 = 684	,
		S_685 = 685	,
		S_686 = 686	,
		S_687 = 687	,
		S_688 = 688	,
		S_689 = 689	,
		S_690 = 690	,
		S_691 = 691	,
		S_692 = 692	,
		S_693 = 693	,
		S_694 = 694	,
		S_695 = 695	,
		S_696 = 696	,
		S_697 = 697	,
		S_698 = 698	,
		S_699 = 699	,
		S_700 = 700	,
		S_701 = 701	,
		S_702 = 702	,
		S_703 = 703	,
		S_704 = 704	,
		S_705 = 705	,
		S_706 = 706	,
		S_707 = 707	,
		S_708 = 708	,
		S_709 = 709	,
		S_710 = 710	,
		S_711 = 711	,
		S_712 = 712	,
		S_713 = 713	,
		S_714 = 714	,
		S_715 = 715	,
		S_716 = 716	,
		S_717 = 717	,
		S_718 = 718	,
		S_719 = 719	,
		S_720 = 720	,
		S_721 = 721	,
		S_722 = 722	,
		S_723 = 723	,
		S_724 = 724	,
		S_725 = 725	,
		S_726 = 726	,
		S_727 = 727	,
		S_728 = 728	,
		S_729 = 729	,
		S_730 = 730	,
		S_731 = 731	,
		S_732 = 732	,
		S_733 = 733	,
		S_734 = 734	,
		S_735 = 735	,
		S_736 = 736	,
		S_737 = 737	,
		S_738 = 738	,
		S_739 = 739	,
		S_740 = 740	,
		S_741 = 741	,
		S_742 = 742	,
		S_743 = 743	,
		S_744 = 744	,
		S_745 = 745	,
		S_746 = 746	,
		S_747 = 747	,
		S_748 = 748	,
		S_749 = 749	,
		S_750 = 750	,
		S_751 = 751	,
		S_752 = 752	,
		S_753 = 753	,
		S_754 = 754	,
		S_755 = 755	,
		S_756 = 756	,
		S_757 = 757	,
		S_758 = 758	,
		S_759 = 759	,
		S_760 = 760	,
		S_761 = 761	,
		S_762 = 762	,
		S_763 = 763	,
		S_764 = 764	,
		S_765 = 765	,
		S_766 = 766	,
		S_767 = 767	,
		S_768 = 768	,
		S_769 = 769	,
		S_770 = 770	,
		S_771 = 771	,
		S_772 = 772	,
		S_773 = 773	,
		S_774 = 774	,
		S_775 = 775	,
		S_776 = 776	,
		S_777 = 777	,
		S_778 = 778	,
		S_779 = 779	,
		S_780 = 780	,
		S_781 = 781	,
		S_782 = 782	,
		S_783 = 783	,
		S_784 = 784	,
		S_785 = 785	,
		S_786 = 786	,
		S_787 = 787	,
		S_788 = 788	,
		S_789 = 789	,
		S_790 = 790	,
		S_791 = 791	,
		S_792 = 792	,
		S_793 = 793	,
		S_794 = 794	,
		S_795 = 795	,
		S_796 = 796	,
		S_797 = 797	,
		S_798 = 798	,
		S_799 = 799	,
		S_800 = 800	,
		S_801 = 801	,
		S_802 = 802	,
		S_803 = 803	,
		S_804 = 804	,
		S_805 = 805	,
		S_806 = 806	,
		S_807 = 807	,
		S_808 = 808	,
		S_809 = 809	,
		S_810 = 810	,
		S_811 = 811	,
		S_812 = 812	,
		S_813 = 813	,
		S_814 = 814	,
		S_815 = 815	,
		S_816 = 816	,
		S_817 = 817	,
		S_818 = 818	,
		S_819 = 819	,
		S_820 = 820	,
		S_821 = 821	,
		S_822 = 822	,
		S_823 = 823	,
		S_824 = 824	,
		S_825 = 825	,
		S_826 = 826	,
		S_827 = 827	,
		S_828 = 828	,
		S_829 = 829	,
		S_830 = 830	,
		S_831 = 831	,
		S_832 = 832	,
		S_833 = 833	,
		S_834 = 834	,
		S_835 = 835	,
		S_836 = 836	,
		S_837 = 837	,
		S_838 = 838	,
		S_839 = 839	,
		S_840 = 840	,
		S_841 = 841	,
		S_842 = 842	,
		S_843 = 843	,
		S_844 = 844	,
		S_845 = 845	,
		S_846 = 846	,
		S_847 = 847	,
		S_848 = 848	,
		S_849 = 849	,
		S_850 = 850	,
		S_851 = 851	,
		S_852 = 852	,
		S_853 = 853	,
		S_854 = 854	,
		S_855 = 855	,
		S_856 = 856	,
		S_857 = 857	,
		S_858 = 858	,
		S_859 = 859	,
		S_860 = 860	,
		S_861 = 861	,
		S_862 = 862	,
		S_863 = 863	,
		S_864 = 864	,
		S_865 = 865	,
		S_866 = 866	,
		S_867 = 867	,
		S_868 = 868	,
		S_869 = 869	,
		S_870 = 870	,
		S_871 = 871	,
		S_872 = 872	,
		S_873 = 873	,
		S_874 = 874	,
		S_875 = 875	,
		S_876 = 876	,
		S_877 = 877	,
		S_878 = 878	,
		S_879 = 879	,
		S_880 = 880	,
		S_881 = 881	,
		S_882 = 882	,
		S_883 = 883	,
		S_884 = 884	,
		S_885 = 885	,
		S_886 = 886	,
		S_887 = 887	,
		S_888 = 888	,
		S_889 = 889	,
		S_890 = 890	,
		S_891 = 891	,
		S_892 = 892	,
		S_893 = 893	,
		S_894 = 894	,
		S_895 = 895	,
		S_896 = 896	,
		S_897 = 897	,
		S_898 = 898	,
		S_899 = 899	,
		S_900 = 900	,
		S_901 = 901	,
		S_902 = 902	,
		S_903 = 903	,
		S_904 = 904	,
		S_905 = 905	,
		S_906 = 906	,
		S_907 = 907	,
		S_908 = 908	,
		S_909 = 909	,
		S_910 = 910	,
		S_911 = 911	,
		S_912 = 912	,
		S_913 = 913	,
		S_914 = 914	,
		S_915 = 915	,
		S_916 = 916	,
		S_917 = 917	,
		S_918 = 918	,
		S_919 = 919	,
		S_920 = 920	,
		S_921 = 921	,
		S_922 = 922	,
		S_923 = 923	,
		S_924 = 924	,
		S_925 = 925	,
		S_926 = 926	,
		S_927 = 927	,
		S_928 = 928	,
		S_929 = 929	,
		S_930 = 930	,
		S_931 = 931	,
		S_932 = 932	,
		S_933 = 933	,
		S_934 = 934	,
		S_935 = 935	,
		S_936 = 936	,
		S_937 = 937	,
		S_938 = 938	,
		S_939 = 939	,
		S_940 = 940	,
		S_941 = 941	,
		S_942 = 942	,
		S_943 = 943	,
		S_944 = 944	,
		S_945 = 945	,
		S_946 = 946	,
		S_947 = 947	,
		S_948 = 948	,
		S_949 = 949	,
		S_950 = 950	,
		S_951 = 951	,
		S_952 = 952	,
		S_953 = 953	,
		S_954 = 954	,
		S_955 = 955	,
		S_956 = 956	,
		S_957 = 957	,
		S_958 = 958	,
		S_959 = 959	,
		S_960 = 960	,
		S_961 = 961	,
		S_962 = 962	,
		S_963 = 963	,
		S_964 = 964	,
		S_965 = 965	,
		S_966 = 966	,
		S_967 = 967	,
		S_968 = 968	,
		S_969 = 969	,
		S_970 = 970	,
		S_971 = 971	,
		S_972 = 972	,
		S_973 = 973	,
		S_974 = 974	,
		S_975 = 975	,
		S_976 = 976	,
		S_977 = 977	,
		S_978 = 978	,
		S_979 = 979	,
		S_980 = 980	,
		S_981 = 981	,
		S_982 = 982	,
		S_983 = 983	,
		S_984 = 984	,
		S_985 = 985	,
		S_986 = 986	,
		S_987 = 987	,
		S_988 = 988	,
		S_989 = 989	,
		S_990 = 990	,
		S_991 = 991	,
		S_992 = 992	,
		S_993 = 993	,
		S_994 = 994	,
		S_995 = 995	,
		S_996 = 996	,
		S_997 = 997	,
		S_998 = 998	,
		S_999 = 999
	};

	std::wstring GetProductAsString(S100_DataProduct product);
}