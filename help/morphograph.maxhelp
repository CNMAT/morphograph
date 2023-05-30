{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 3,
			"revision" : 3,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 196.0, 129.0, 985.0, 642.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 0,
		"lefttoolbarpinned" : 2,
		"toptoolbarpinned" : 2,
		"righttoolbarpinned" : 2,
		"bottomtoolbarpinned" : 2,
		"toolbars_unpinned_last_save" : 15,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "Untitled5_template",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-54",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 59.0, 104.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "Untitled5_template",
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 100.0, 95.0, 24.0 ],
									"text" : "prepend open"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-29",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "bang" ],
									"patching_rect" : [ 118.0, 134.0, 53.0, 24.0 ],
									"text" : "sfplay~"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-43",
									"index" : 2,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 94.0, 36.0, 30.0, 30.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-51",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 28.0, 36.0, 30.0, 30.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-53",
									"index" : 1,
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.0, 216.0, 30.0, 30.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"source" : [ "obj-43", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"source" : [ "obj-51", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 441.5, 482.0, 66.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 14.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p playback"
				}

			}
, 			{
				"box" : 				{
					"channels" : 1,
					"id" : "obj-38",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 441.5, 512.0, 37.0, 107.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "out",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_shortname" : "out",
							"parameter_type" : 0,
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 488.0, 587.5, 32.0, 32.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 413.0, 482.0, 22.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Lato",
					"fontsize" : 13.0,
					"id" : "obj-27",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 101.0, 94.0, 426.0, 53.0 ],
					"text" : "The Ocular Scores Morphograph object performs user-specified analyses on audio material.  It allows the user to choose how these analyses will affect graphic objects in an output SVG score",
					"textcolor" : [ 0.537254901960784, 0.537254901960784, 0.537254901960784, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Lato",
					"fontsize" : 13.0,
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 101.0, 68.0, 372.0, 22.0 ],
					"text" : "analyze an audio buffer, and export graphic score elements"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Lato",
					"fontsize" : 36.0,
					"id" : "obj-17",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 101.0, 27.0, 611.0, 50.0 ],
					"text" : "Ocular Scores, featuring Morphograph"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 859.0, 452.0, 58.0, 22.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"linecount" : 4,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 859.0, 482.0, 114.0, 62.0 ],
					"text" : "/Users/jml/Documents/freelance/linda_bouchard/mgraph_project/demo/"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-49",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 308.5, 208.0, 22.0, 20.0 ],
					"text" : "3. ",
					"textcolor" : [ 0.988235294117647, 0.0, 0.996078431372549, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-47",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 816.0, 363.0, 150.0, 20.0 ],
					"text" : "1. define SVG write path",
					"textcolor" : [ 0.988235294117647, 0.0, 0.996078431372549, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-19",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ],
					"patching_rect" : [ 790.0, 421.0, 90.0, 22.0 ],
					"text" : "regexp .+:(.+)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 790.0, 363.0, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"patching_rect" : [ 790.0, 397.0, 90.0, 22.0 ],
					"text" : "opendialog fold"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 326.5, 208.0, 51.0, 22.0 ],
					"text" : "process"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-52",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 59.0, 104.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "Untitled5_template",
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-27",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 253.0, 160.0, 50.0, 24.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"linecount" : 2,
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 183.0, 193.5, 45.0, 40.0 ],
									"text" : "/ 1000."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 55.0, 247.0, 109.0, 24.0 ],
									"text" : "416990."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 104.0, 197.0, 30.0, 24.0 ],
									"text" : "* 1."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-36",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 41.0, 152.0, 50.0, 40.0 ],
									"text" : "44100."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-34",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 104.0, 100.0, 24.0, 24.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-17",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 9,
									"outlettype" : [ "float", "list", "float", "float", "float", "float", "float", "", "int" ],
									"patching_rect" : [ 104.0, 134.0, 103.0, 24.0 ],
									"text" : "info~ morph1"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-51",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 104.0, 40.0, 30.0, 30.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 1 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"source" : [ "obj-17", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"order" : 0,
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-27", 0 ],
									"source" : [ "obj-17", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 1 ],
									"order" : 1,
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 1 ],
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-34", 0 ],
									"source" : [ "obj-51", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 295.0, 587.5, 51.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 14.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p length"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-50",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 576.0, 155.5, 150.0, 33.0 ],
					"text" : "2. dbl-click for example specification; edit",
					"textcolor" : [ 0.988235294117647, 0.0, 0.996078431372549, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-48",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 34.0, 303.0, 94.0, 20.0 ],
					"text" : "post information"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-46",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 37.0, 186.0, 93.0, 20.0 ],
					"text" : "set active buffer"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 192.0, 186.0, 110.0, 20.0 ],
					"text" : "set svg export path"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-26",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 413.0, 186.0, 124.0, 20.0 ],
					"text" : "load svg file from disk"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 399.0, 155.5, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 399.0, 233.0, 79.0, 22.0 ],
					"text" : "prepend load"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-39",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"patching_rect" : [ 399.0, 208.0, 133.0, 22.0 ],
					"text" : "opendialog @types svg"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 87.0, 187.0, 1027.0, 537.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "Untitled5_template",
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontface" : 2,
									"fontsize" : 12.0,
									"id" : "obj-1",
									"linecount" : 6,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 796.0, 367.0, 143.0, 87.0 ],
									"text" : "hint:  the transform properties that you issue with the input dictionary determine the default dimensions for the generated shapes."
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-63",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.0, 195.0, 147.0, 24.0 ],
									"text" : "elt - elongated triangle",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-62",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.0, 220.0, 85.0, 24.0 ],
									"text" : "stereoscope",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-61",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.0, 169.0, 170.0, 24.0 ],
									"text" : "tab - triangle attack-based",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-54",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.0, 140.142602495543656, 54.0, 24.0 ],
									"text" : "triangle",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-55",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.0, 113.051693404634534, 61.0, 24.0 ],
									"text" : "crescent",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-56",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.0, 85.960784313725412, 32.0, 24.0 ],
									"text" : "rect",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-58",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.0, 59.960784313725526, 41.0, 24.0 ],
									"text" : "circle",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-60",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 690.0, 26.0, 144.0, 22.0 ],
									"text" : "shapes:"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-48",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 866.0, 195.454545454545467, 132.0, 24.0 ],
									"text" : "x (deviation thereof)",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-49",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 866.0, 168.363636363636374, 29.5, 24.0 ],
									"text" : "y",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-50",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 866.0, 141.27272727272728, 47.0, 24.0 ],
									"text" : "height",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-51",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 866.0, 114.181818181818187, 41.0, 24.0 ],
									"text" : "width",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-52",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 866.0, 87.090909090909093, 33.0, 24.0 ],
									"text" : "size",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-53",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 866.0, 60.0, 55.0, 24.0 ],
									"text" : "rotation",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-43",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 866.0, 26.0, 144.0, 22.0 ],
									"text" : "actions:"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "live.line",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 13.0, 647.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-41",
									"maxclass" : "live.line",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 400.0, 647.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"hidden" : 1,
									"id" : "obj-40",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 462.0, 552.0, 157.0, 40.0 ],
									"text" : ";\rmax launch_browser $1"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-36",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 330.909090909090878, 397.0, 24.0 ],
									"text" : "https://en.wikipedia.org/wiki/High_frequency_content_measure"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-35",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 357.999999999999943, 266.0, 24.0 ],
									"text" : "https://en.wikipedia.org/wiki/Inharmonicity"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-34",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 303.818181818181813, 384.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectralcrest.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-33",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 276.727272727272748, 402.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectralflatness.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-32",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 249.636363636363626, 387.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectralslope.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-31",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 222.545454545454561, 412.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectraldecrease.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-30",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 195.673119705951422, 524.0, 24.0 ],
									"text" : "https://www.researchgate.net/figure/Spectral-irregularity-calculation_fig1_26620188"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-29",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 168.363636363636374, 376.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectralflux.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-28",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 141.27272727272728, 402.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectralkurtosis.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-27",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 114.181818181818187, 415.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectralskewness.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 87.090909090909093, 397.0, 24.0 ],
									"text" : "https://www.mathworks.com/help/audio/ref/spectralspread.html"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-25",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 60.0, 292.0, 24.0 ],
									"text" : "https://en.wikipedia.org/wiki/Spectral_centroid"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-24",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 357.999999999999943, 91.0, 24.0 ],
									"text" : "inharmonicity",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-23",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 330.909090909090878, 29.5, 24.0 ],
									"text" : "hfc",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-22",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 303.818181818181813, 68.0, 24.0 ],
									"text" : "speccrest",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-21",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 276.727272727272748, 57.0, 24.0 ],
									"text" : "specflat",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-16",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 249.636363636363626, 72.0, 24.0 ],
									"text" : "specslope",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-15",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 222.545454545454561, 65.0, 24.0 ],
									"text" : "specdecr",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 195.454545454545467, 51.0, 24.0 ],
									"text" : "specirr",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-13",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 168.363636363636374, 60.0, 24.0 ],
									"text" : "specflux",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 141.27272727272728, 61.0, 24.0 ],
									"text" : "speckurt",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 114.181818181818187, 70.0, 24.0 ],
									"text" : "specskew",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-10",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 87.090909090909093, 81.0, 24.0 ],
									"text" : "specspread",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-9",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 60.0, 69.0, 24.0 ],
									"text" : "speccentr",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 477.0, 430.0, 24.0 ],
									"text" : "https://www.sciencedirect.com/topics/engineering/zero-crossing-rate"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 477.0, 29.5, 24.0 ],
									"text" : "zcr",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgcolor2" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color1" : [ 0.517647058823529, 0.517647058823529, 0.486274509803922, 0.4 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-3",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 450.960784313725526, 51.0, 24.0 ],
									"text" : "energy",
									"textcolor" : [ 0.462745098039216, 0.192156862745098, 0.015686274509804, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.388235294117647, 0.458823529411765, 0.482352941176471, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-2",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 450.960784313725526, 356.0, 24.0 ],
									"text" : "https://en.wikipedia.org/wiki/Energy_(signal_processing)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 417.0, 144.0, 22.0 ],
									"text" : "desc temporal:"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 0,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 8,
											"minor" : 3,
											"revision" : 3,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"classnamespace" : "box",
										"rect" : [ 153.0, 91.0, 1001.0, 783.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 14.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 1,
										"objectsnaponopen" : 1,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"lefttoolbarpinned" : 0,
										"toptoolbarpinned" : 0,
										"righttoolbarpinned" : 0,
										"bottomtoolbarpinned" : 0,
										"toolbars_unpinned_last_save" : 0,
										"tallnewobj" : 0,
										"boxanimatetime" : 200,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"style" : "",
										"subpatcher_template" : "Untitled5_template",
										"assistshowspatchername" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-5",
													"linecount" : 8,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 495.0, 186.0, 412.0, 132.0 ],
													"text" : "actions:\n\n\trotation\n\tsize\n\twidth (from left of object)\n\theight (from bottom of object)\n\ty (x is always time)\n\tx (only deviation/offset from timestamp as x progresses naturally)"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-4",
													"linecount" : 19,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 100.0, 422.0, 304.0 ],
													"text" : "orig shapes:\n\n\tcrescent\n\ttriangle (swell based)\n\t* triangle (jml - attack based)\n\telongated triangle\n\tellipse \n\t* stereoscope (oscilloscope shape) - ask joseph\n\t* mixed - rule-based; if there is a particular thing happening, change the shape\n\n\tcircle with noise scaling; open vs closed drone based; slow movements \n\ttriangle - open vs closed; see peaks; attack-based\n\t* look into the \"obtuse\" triangle that is elongated\n\n\t- filled vs outline\n\t- * noise parameter on all\n\t- * attacks vs swells vs lines "
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-3",
													"linecount" : 9,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 529.0, 145.0, 163.0 ],
													"text" : "colors:\n\n\tblue - subdued (piano); transparent\n\tmagenta/red - more loud (mezzo forte); dense\n\twhite - normal (forte); regular\n"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-2",
													"linecount" : 6,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 419.0, 144.0, 100.0 ],
													"text" : "static choices:\n\n\tnoise amount \n\tcolor\n\tshape \n\tbuffer choice "
												}

											}
 ],
										"lines" : [  ]
									}
,
									"patching_rect" : [ 796.0, 470.960784313725526, 118.0, 24.0 ],
									"saved_object_attributes" : 									{
										"description" : "",
										"digest" : "",
										"fontsize" : 14.0,
										"globalpatchername" : "",
										"tags" : ""
									}
,
									"text" : "p original_options"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-38",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 26.0, 144.0, 22.0 ],
									"text" : "desc spectral:"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-31", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-33", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-35", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"hidden" : 1,
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 790.0, 306.152261123267749, 122.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 14.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p \"mapping api / info\""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-40",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 117.0, 540.0, 95.0, 22.0 ],
					"text" : "prepend replace"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 49.0, 474.0, 85.0, 22.0 ],
					"text" : "prepend prefix"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-33",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 49.0, 445.0, 80.0, 22.0 ],
					"text" : "r morphopath"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 808.0, 575.652261123267749, 82.0, 22.0 ],
					"text" : "s morphopath"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 180.0, 155.5, 80.0, 22.0 ],
					"text" : "r morphopath"
				}

			}
, 			{
				"box" : 				{
					"autopopulate" : 1,
					"id" : "obj-25",
					"items" : [ "Allora_1_prt1.aif", ",", "BassGesture.aif", ",", "BowedCymbalNORM.wav", ",", "Brahms_4.wav", ",", "Calzadilla_1.aif", ",", "Coda_Box3_a.aif", ",", "Cymbal_onHead2.wav", ",", "Koonitz.wav", ",", "LoriFreedman_Improv4.wav", ",", "Meandre_1.aif", ",", "Pointillistic.aif", ",", "ReceidingSimple.aif", ",", "Scen2Box(a).aif", ",", "scene 3-box 4.aif", ",", "SustainedTextured_Crackel-Mix.aif", ",", "tongue6.wav", ",", "tongue7_FH.wav", ",", "TrombDrum.wav" ],
					"maxclass" : "umenu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 49.0, 513.0, 155.0, 22.0 ],
					"prefix" : "~/Documents/freelance/linda_bouchard/mgraph_project/demo/",
					"types" : [ "WAVE", "AIFF", "MP3" ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 24.0, 155.5, 58.0, 22.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 3,
							"revision" : 3,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 59.0, 104.0, 454.0, 501.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "Untitled5_template",
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-6",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 219.0, 125.847738876732251, 154.0, 38.0 ],
									"text" : "auto-draw graph after render to disk"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"linecount" : 5,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 219.0, 28.847738876732251, 154.0, 85.0 ],
									"text" : "draw text with information about graph, including last loaded file and other stats"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-29",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 194.0, 313.0, 66.0, 24.0 ],
									"text" : "loadbang"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"linecount" : 3,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 194.0, 345.847738876732251, 183.0, 55.0 ],
									"text" : "/Users/jml/Documents/freelance/linda_bouchard/mgraph_project/mgraph_patchers/"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 219.0, 180.847738876732251, 154.0, 38.0 ],
									"text" : "update main path for SVG writing..."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 382.847738876732251, 154.0, 69.0 ],
									"text" : "analysis needs to be re-calculated if buffer changes; need to warn user about this"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 303.847738876732251, 150.0, 69.0 ],
									"text" : "user should be able to change shape and re-calculate without re-triggering analysis"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 148.847738876732251, 150.0, 22.0 ],
									"text" : "add layers"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-43",
									"linecount" : 5,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 42.0, 182.0, 100.0 ],
									"text" : "notes for this helpfile:\n\nrecording of buffer~ \ntesting for all combinations  \ncredits\n"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-19",
									"linecount" : 6,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 180.847738876732251, 150.0, 100.0 ],
									"text" : "desired API:\n\n/layer/0/descmap\n/shape \n\n...integrate w/ odot"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"source" : [ "obj-29", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 790.0, 332.152261123267749, 80.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 14.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p notes/goals"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 726.0, 186.0, 150.0, 20.0 ],
					"text" : "errors if cannot find"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 180.0, 208.0, 102.0, 22.0 ],
					"text" : "prepend set_path"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "dictionary" ],
					"patching_rect" : [ 550.0, 254.0, 29.0, 22.0 ],
					"text" : "thru"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 550.0, 107.5, 44.5, 44.5 ]
				}

			}
, 			{
				"box" : 				{
					"data" : 					{
						"filename" : "mgraph_example.svg",
						"shape" : "triangles",
						"style" : "both",
						"descmap" : 						{
							"energy" : "size",
							"speccrest" : "xscale",
							"speckurt" : "brightness",
							"zcr" : "ylocation"
						}
,
						"transform" : 						{
							"width" : 600,
							"height" : 600,
							"zoom" : 1
						}

					}
,
					"id" : "obj-21",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 4,
					"outlettype" : [ "dictionary", "", "", "" ],
					"patching_rect" : [ 550.0, 208.0, 164.0, 22.0 ],
					"saved_object_attributes" : 					{
						"embed" : 1,
						"parameter_enable" : 0,
						"parameter_mappable" : 0
					}
,
					"text" : "dict morphograph @embed 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-18",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 180.0, 477.0, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-20",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 726.0, 208.0, 89.0, 22.0 ],
					"text" : "dictionary putty"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"maxclass" : "dict.view",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 550.0, 303.0, 207.0, 264.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "morphograph",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"p_hopsize" : 1024,
					"patching_rect" : [ 180.0, 299.65226100000001, 357.0, 162.999999999999943 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 117.0, 563.5, 197.0, 22.0 ],
					"text" : "buffer~ morph1 Brahms_4.wav -1 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 38.0, 267.0, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 24.0, 208.0, 69.0, 22.0 ],
					"text" : "set morph1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 95.0, 208.0, 33.0, 22.0 ],
					"text" : "view"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"source" : [ "obj-19", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"order" : 1,
					"source" : [ "obj-25", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 1 ],
					"hidden" : 1,
					"order" : 0,
					"source" : [ "obj-25", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"order" : 1,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"order" : 0,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 0 ],
					"hidden" : 1,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 1 ],
					"hidden" : 1,
					"order" : 0,
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 0 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"source" : [ "obj-6", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-38" : [ "out", "out", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "morphograph.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "thru.maxpat",
				"bootpath" : "C74:/patchers/m4l/Pluggo for Live resources/patches",
				"type" : "JSON",
				"implicit" : 1
			}
 ],
		"autosave" : 0,
		"bgcolor" : [ 0.803921568627451, 0.850980392156863, 0.850980392156863, 1.0 ]
	}

}
