;
; vector.asm
;
; A machine generated vector table
; for 680x0 family CPU
;


initial_stack     EQU   $80000
initial_pc        EQU   $00FC0400

ipl1_handler      EQU   common_handler
ipl2_handler      EQU   common_handler
ipl3_handler      EQU   common_handler
ipl4_handler      EQU   common_handler
ipl5_handler      EQU   common_handler
ipl7_handler      EQU   common_handler

trap0_handler     EQU   common_handler
trap2_handler     EQU   common_handler
trap3_handler     EQU   common_handler
trap4_handler     EQU   common_handler
trap5_handler     EQU   common_handler
trap6_handler     EQU   common_handler
trap7_handler     EQU   common_handler
trap8_handler     EQU   common_handler
trap9_handler     EQU   common_handler
trap10_handler    EQU   common_handler
trap11_handler    EQU   common_handler
trap12_handler    EQU   common_handler
trap13_handler    EQU   common_handler
trap14_handler    EQU   common_handler
trap15_handler    EQU   common_handler


vector_table:
	dc.l initial_stack
	dc.l initial_pc
	dc.l common_handler   ; vector 2
	dc.l common_handler   ; vector 3
	dc.l common_handler   ; vector 4
	dc.l common_handler   ; vector 5
	dc.l common_handler   ; vector 6
	dc.l common_handler   ; vector 7

	dc.l common_handler   ; vector 8
	dc.l common_handler   ; vector 9
	dc.l common_handler   ; vector 10
	dc.l common_handler   ; vector 11
	dc.l common_handler   ; vector 12
	dc.l common_handler   ; vector 13
	dc.l common_handler   ; vector 14
	dc.l common_handler   ; vector 15

	dc.l common_handler   ; vector 16
	dc.l common_handler   ; vector 17
	dc.l common_handler   ; vector 18
	dc.l common_handler   ; vector 19
	dc.l common_handler   ; vector 20
	dc.l common_handler   ; vector 21
	dc.l common_handler   ; vector 22
	dc.l common_handler   ; vector 23

	dc.l common_handler   ; vector 24
	dc.l common_handler   ; vector 25
	dc.l common_handler   ; vector 26
	dc.l common_handler   ; vector 27
	dc.l common_handler   ; vector 28
	dc.l common_handler   ; vector 29
	dc.l ipl6_handler     ; vector 30
	dc.l common_handler   ; vector 31

	dc.l common_handler   ; vector 32
	dc.l trap1_handler    ; vector 33
	dc.l common_handler   ; vector 34
	dc.l common_handler   ; vector 35
	dc.l common_handler   ; vector 36
	dc.l common_handler   ; vector 37
	dc.l common_handler   ; vector 38
	dc.l common_handler   ; vector 39

	dc.l common_handler   ; vector 40
	dc.l common_handler   ; vector 41
	dc.l common_handler   ; vector 42
	dc.l common_handler   ; vector 43
	dc.l common_handler   ; vector 44
	dc.l common_handler   ; vector 45
	dc.l common_handler   ; vector 46
	dc.l common_handler   ; vector 47

	dc.l common_handler   ; vector 48
	dc.l common_handler   ; vector 49
	dc.l common_handler   ; vector 50
	dc.l common_handler   ; vector 51
	dc.l common_handler   ; vector 52
	dc.l common_handler   ; vector 53
	dc.l common_handler   ; vector 54
	dc.l common_handler   ; vector 55

	dc.l common_handler   ; vector 56
	dc.l common_handler   ; vector 57
	dc.l common_handler   ; vector 58
	dc.l common_handler   ; vector 59
	dc.l common_handler   ; vector 60
	dc.l common_handler   ; vector 61
	dc.l common_handler   ; vector 62
	dc.l common_handler   ; vector 63

	dc.l common_handler   ; vector 64
	dc.l common_handler   ; vector 65
	dc.l common_handler   ; vector 66
	dc.l common_handler   ; vector 67
	dc.l common_handler   ; vector 68
	dc.l common_handler   ; vector 69
	dc.l common_handler   ; vector 70
	dc.l common_handler   ; vector 71

	dc.l common_handler   ; vector 72
	dc.l common_handler   ; vector 73
	dc.l common_handler   ; vector 74
	dc.l common_handler   ; vector 75
	dc.l common_handler   ; vector 76
	dc.l common_handler   ; vector 77
	dc.l common_handler   ; vector 78
	dc.l common_handler   ; vector 79

	dc.l common_handler   ; vector 80
	dc.l common_handler   ; vector 81
	dc.l common_handler   ; vector 82
	dc.l common_handler   ; vector 83
	dc.l common_handler   ; vector 84
	dc.l common_handler   ; vector 85
	dc.l common_handler   ; vector 86
	dc.l common_handler   ; vector 87

	dc.l common_handler   ; vector 88
	dc.l common_handler   ; vector 89
	dc.l common_handler   ; vector 90
	dc.l common_handler   ; vector 91
	dc.l common_handler   ; vector 92
	dc.l common_handler   ; vector 93
	dc.l common_handler   ; vector 94
	dc.l common_handler   ; vector 95

	dc.l common_handler   ; vector 96
	dc.l common_handler   ; vector 97
	dc.l common_handler   ; vector 98
	dc.l common_handler   ; vector 99
	dc.l common_handler   ; vector 100
	dc.l common_handler   ; vector 101
	dc.l common_handler   ; vector 102
	dc.l common_handler   ; vector 103

	dc.l common_handler   ; vector 104
	dc.l common_handler   ; vector 105
	dc.l common_handler   ; vector 106
	dc.l common_handler   ; vector 107
	dc.l common_handler   ; vector 108
	dc.l common_handler   ; vector 109
	dc.l common_handler   ; vector 110
	dc.l common_handler   ; vector 111

	dc.l common_handler   ; vector 112
	dc.l common_handler   ; vector 113
	dc.l common_handler   ; vector 114
	dc.l common_handler   ; vector 115
	dc.l common_handler   ; vector 116
	dc.l common_handler   ; vector 117
	dc.l common_handler   ; vector 118
	dc.l common_handler   ; vector 119

	dc.l common_handler   ; vector 120
	dc.l common_handler   ; vector 121
	dc.l common_handler   ; vector 122
	dc.l common_handler   ; vector 123
	dc.l common_handler   ; vector 124
	dc.l common_handler   ; vector 125
	dc.l common_handler   ; vector 126
	dc.l common_handler   ; vector 127

	dc.l common_handler   ; vector 128
	dc.l common_handler   ; vector 129
	dc.l common_handler   ; vector 130
	dc.l common_handler   ; vector 131
	dc.l common_handler   ; vector 132
	dc.l common_handler   ; vector 133
	dc.l common_handler   ; vector 134
	dc.l common_handler   ; vector 135

	dc.l common_handler   ; vector 136
	dc.l common_handler   ; vector 137
	dc.l common_handler   ; vector 138
	dc.l common_handler   ; vector 139
	dc.l common_handler   ; vector 140
	dc.l common_handler   ; vector 141
	dc.l common_handler   ; vector 142
	dc.l common_handler   ; vector 143

	dc.l common_handler   ; vector 144
	dc.l common_handler   ; vector 145
	dc.l common_handler   ; vector 146
	dc.l common_handler   ; vector 147
	dc.l common_handler   ; vector 148
	dc.l common_handler   ; vector 149
	dc.l common_handler   ; vector 150
	dc.l common_handler   ; vector 151

	dc.l common_handler   ; vector 152
	dc.l common_handler   ; vector 153
	dc.l common_handler   ; vector 154
	dc.l common_handler   ; vector 155
	dc.l common_handler   ; vector 156
	dc.l common_handler   ; vector 157
	dc.l common_handler   ; vector 158
	dc.l common_handler   ; vector 159

	dc.l common_handler   ; vector 160
	dc.l common_handler   ; vector 161
	dc.l common_handler   ; vector 162
	dc.l common_handler   ; vector 163
	dc.l common_handler   ; vector 164
	dc.l common_handler   ; vector 165
	dc.l common_handler   ; vector 166
	dc.l common_handler   ; vector 167

	dc.l common_handler   ; vector 168
	dc.l common_handler   ; vector 169
	dc.l common_handler   ; vector 170
	dc.l common_handler   ; vector 171
	dc.l common_handler   ; vector 172
	dc.l common_handler   ; vector 173
	dc.l common_handler   ; vector 174
	dc.l common_handler   ; vector 175

	dc.l common_handler   ; vector 176
	dc.l common_handler   ; vector 177
	dc.l common_handler   ; vector 178
	dc.l common_handler   ; vector 179
	dc.l common_handler   ; vector 180
	dc.l common_handler   ; vector 181
	dc.l common_handler   ; vector 182
	dc.l common_handler   ; vector 183

	dc.l common_handler   ; vector 184
	dc.l common_handler   ; vector 185
	dc.l common_handler   ; vector 186
	dc.l common_handler   ; vector 187
	dc.l common_handler   ; vector 188
	dc.l common_handler   ; vector 189
	dc.l common_handler   ; vector 190
	dc.l common_handler   ; vector 191

	dc.l common_handler   ; vector 192
	dc.l common_handler   ; vector 193
	dc.l common_handler   ; vector 194
	dc.l common_handler   ; vector 195
	dc.l common_handler   ; vector 196
	dc.l common_handler   ; vector 197
	dc.l common_handler   ; vector 198
	dc.l common_handler   ; vector 199

	dc.l common_handler   ; vector 200
	dc.l common_handler   ; vector 201
	dc.l common_handler   ; vector 202
	dc.l common_handler   ; vector 203
	dc.l common_handler   ; vector 204
	dc.l common_handler   ; vector 205
	dc.l common_handler   ; vector 206
	dc.l common_handler   ; vector 207

	dc.l common_handler   ; vector 208
	dc.l common_handler   ; vector 209
	dc.l common_handler   ; vector 210
	dc.l common_handler   ; vector 211
	dc.l common_handler   ; vector 212
	dc.l common_handler   ; vector 213
	dc.l common_handler   ; vector 214
	dc.l common_handler   ; vector 215

	dc.l common_handler   ; vector 216
	dc.l common_handler   ; vector 217
	dc.l common_handler   ; vector 218
	dc.l common_handler   ; vector 219
	dc.l common_handler   ; vector 220
	dc.l common_handler   ; vector 221
	dc.l common_handler   ; vector 222
	dc.l common_handler   ; vector 223

	dc.l common_handler   ; vector 224
	dc.l common_handler   ; vector 225
	dc.l common_handler   ; vector 226
	dc.l common_handler   ; vector 227
	dc.l common_handler   ; vector 228
	dc.l common_handler   ; vector 229
	dc.l common_handler   ; vector 230
	dc.l common_handler   ; vector 231

	dc.l common_handler   ; vector 232
	dc.l common_handler   ; vector 233
	dc.l common_handler   ; vector 234
	dc.l common_handler   ; vector 235
	dc.l common_handler   ; vector 236
	dc.l common_handler   ; vector 237
	dc.l common_handler   ; vector 238
	dc.l common_handler   ; vector 239

	dc.l common_handler   ; vector 240
	dc.l common_handler   ; vector 241
	dc.l common_handler   ; vector 242
	dc.l common_handler   ; vector 243
	dc.l common_handler   ; vector 244
	dc.l common_handler   ; vector 245
	dc.l common_handler   ; vector 246
	dc.l common_handler   ; vector 247

	dc.l common_handler   ; vector 248
	dc.l common_handler   ; vector 249
	dc.l common_handler   ; vector 250
	dc.l common_handler   ; vector 251
	dc.l common_handler   ; vector 252
	dc.l common_handler   ; vector 253
	dc.l common_handler   ; vector 254
	dc.l common_handler   ; vector 255



