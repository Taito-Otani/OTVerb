#include "gen_exported.h"

namespace gen_exported {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_11;
	Delay m_delay_10;
	Delay m_delay_12;
	Delay m_delay_6;
	Delay m_delay_7;
	Delay m_delay_8;
	Delay m_delay_13;
	Delay m_delay_15;
	Delay m_delay_14;
	Delay m_delay_17;
	Delay m_delay_16;
	Delay m_delay_9;
	int __exception;
	int vectorsize;
	t_sample m_spread_20;
	t_sample m_dry_19;
	t_sample m_tail_24;
	t_sample m_damping_21;
	t_sample m_bandwidth_23;
	t_sample m_roomsize_22;
	t_sample m_history_5;
	t_sample m_early_18;
	t_sample m_history_1;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample m_revtime_25;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_delay_6.reset("m_delay_6", ((int)4900));
		m_delay_7.reset("m_delay_7", ((int)6002));
		m_delay_8.reset("m_delay_8", ((int)16000));
		m_delay_9.reset("m_delay_9", ((int)14000));
		m_delay_10.reset("m_delay_10", ((int)6000));
		m_delay_11.reset("m_delay_11", ((int)10004));
		m_delay_12.reset("m_delay_12", ((int)14000));
		m_delay_13.reset("m_delay_13", ((int)48000));
		m_delay_14.reset("m_delay_14", ((int)48000));
		m_delay_15.reset("m_delay_15", ((int)48000));
		m_delay_16.reset("m_delay_16", ((int)48000));
		m_delay_17.reset("m_delay_17", ((int)48000));
		m_early_18 = ((t_sample)0.25);
		m_dry_19 = ((int)1);
		m_spread_20 = ((int)23);
		m_damping_21 = ((t_sample)0.7);
		m_roomsize_22 = ((int)75);
		m_bandwidth_23 = ((t_sample)0.5);
		m_tail_24 = ((t_sample)0.25);
		m_revtime_25 = ((int)11);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_351 = safepow(((t_sample)0.001), safediv(((int)1), (m_revtime_25 * samplerate)));
		t_sample expr_352 = ((m_roomsize_22 * samplerate) * ((t_sample)0.0029411764705882));
		t_sample add_256 = (expr_352 + ((int)5));
		t_sample expr_346 = safepow(expr_351, add_256);
		t_sample mul_333 = (expr_352 * ((int)1));
		t_sample expr_350 = (-safepow(expr_351, mul_333));
		t_sample mul_331 = (expr_352 * ((t_sample)0.7071));
		t_sample expr_344 = (-safepow(expr_351, mul_331));
		t_sample mul_332 = (expr_352 * ((t_sample)0.81649));
		t_sample expr_345 = (-safepow(expr_351, mul_332));
		t_sample mul_330 = (expr_352 * ((t_sample)0.63245));
		t_sample expr_343 = (-safepow(expr_351, mul_330));
		t_sample mul_261 = (expr_352 * ((t_sample)0.3));
		t_sample add_258 = (mul_261 + ((int)5));
		t_sample expr_348 = safepow(expr_351, add_258);
		t_sample mul_260 = (expr_352 * ((t_sample)0.155));
		t_sample add_257 = (mul_260 + ((int)5));
		t_sample expr_347 = safepow(expr_351, add_257);
		t_sample rsub_341 = (((int)1) - m_bandwidth_23);
		t_sample mul_262 = (expr_352 * ((t_sample)0.41));
		t_sample add_259 = (mul_262 + ((int)5));
		t_sample expr_349 = safepow(expr_351, add_259);
		t_sample mul_327 = (expr_352 * ((t_sample)0.000527));
		int int_326 = int(mul_327);
		t_sample mul_267 = (m_spread_20 * (-0.380445));
		t_sample add_266 = (mul_267 + ((int)931));
		t_sample rsub_263 = (((int)1341) - add_266);
		t_sample mul_276 = (int_326 * rsub_263);
		t_sample mul_295 = (m_spread_20 * ((t_sample)0.376623));
		t_sample add_294 = (mul_295 + ((int)931));
		t_sample rsub_291 = (((int)1341) - add_294);
		t_sample mul_302 = (int_326 * rsub_291);
		t_sample mul_325 = (expr_352 * ((t_sample)0.110732));
		t_sample mul_269 = (m_spread_20 * (-0.568366));
		t_sample add_265 = (mul_269 + ((int)369));
		t_sample rsub_264 = (add_266 - add_265);
		t_sample mul_283 = (int_326 * rsub_264);
		t_sample mul_311 = (m_spread_20 * ((t_sample)0.125541));
		t_sample add_293 = (mul_311 + ((int)369));
		t_sample rsub_292 = (add_294 - add_293);
		t_sample mul_309 = (int_326 * rsub_292);
		t_sample add_268 = (mul_269 + ((int)159));
		t_sample mul_290 = (int_326 * add_268);
		t_sample add_310 = (mul_311 + ((int)159));
		t_sample mul_318 = (int_326 * add_310);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_188 = (in2 * m_dry_19);
			t_sample mul_200 = (in1 * m_dry_19);
			t_sample mul_190 = ((in2 + in1) * ((t_sample)0.708));
			t_sample mix_390 = (mul_190 + (rsub_341 * (m_history_5 - mul_190)));
			t_sample mix_340 = mix_390;
			t_sample tap_230 = m_delay_17.read_linear(mul_330);
			t_sample mul_226 = (tap_230 * expr_343);
			t_sample mix_391 = (mul_226 + (m_damping_21 * (m_history_4 - mul_226)));
			t_sample mix_228 = mix_391;
			t_sample tap_236 = m_delay_16.read_linear(mul_331);
			t_sample mul_232 = (tap_236 * expr_344);
			t_sample mix_392 = (mul_232 + (m_damping_21 * (m_history_3 - mul_232)));
			t_sample mix_234 = mix_392;
			t_sample tap_242 = m_delay_15.read_linear(mul_332);
			t_sample mul_238 = (tap_242 * expr_345);
			t_sample mix_393 = (mul_238 + (m_damping_21 * (m_history_2 - mul_238)));
			t_sample mix_240 = mix_393;
			t_sample tap_338 = m_delay_14.read_linear(mul_333);
			t_sample mul_329 = (tap_338 * expr_350);
			t_sample mix_394 = (mul_329 + (m_damping_21 * (m_history_1 - mul_329)));
			t_sample mix_336 = mix_394;
			t_sample tap_244 = m_delay_13.read_linear(add_259);
			t_sample tap_245 = m_delay_13.read_linear(add_258);
			t_sample tap_246 = m_delay_13.read_linear(add_257);
			t_sample tap_247 = m_delay_13.read_linear(add_256);
			t_sample mul_248 = (tap_247 * expr_346);
			t_sample mul_250 = (tap_246 * expr_347);
			t_sample mul_252 = (tap_245 * expr_348);
			t_sample mul_254 = (tap_244 * expr_349);
			t_sample tap_275 = m_delay_12.read_linear(mul_276);
			t_sample mul_273 = (tap_275 * ((t_sample)0.625));
			t_sample tap_301 = m_delay_11.read_linear(mul_302);
			t_sample mul_299 = (tap_301 * ((t_sample)0.625));
			t_sample add_220 = (mix_336 + mix_240);
			t_sample add_218 = (mix_234 + mix_228);
			t_sample add_213 = (add_220 + add_218);
			t_sample mul_196 = (add_213 * ((t_sample)0.5));
			t_sample add_221 = (mul_196 + mul_248);
			t_sample sub_217 = (add_220 - add_218);
			t_sample mul_199 = (sub_217 * ((t_sample)0.5));
			t_sample add_224 = (mul_199 + mul_254);
			t_sample sub_219 = (mix_336 - mix_240);
			t_sample sub_216 = (mix_234 - mix_228);
			t_sample sub_215 = (sub_219 - sub_216);
			t_sample mul_198 = (sub_215 * ((t_sample)0.5));
			t_sample add_223 = (mul_198 + mul_252);
			t_sample add_214 = (sub_219 + sub_216);
			t_sample rsub_212 = (((int)0) - add_214);
			t_sample mul_197 = (rsub_212 * ((t_sample)0.5));
			t_sample add_222 = (mul_197 + mul_250);
			t_sample tap_324 = m_delay_10.read_linear(mul_325);
			t_sample tap_282 = m_delay_9.read_linear(mul_283);
			t_sample mul_280 = (tap_282 * ((t_sample)0.625));
			t_sample tap_308 = m_delay_8.read_linear(mul_309);
			t_sample mul_306 = (tap_308 * ((t_sample)0.625));
			t_sample mul_322 = (tap_324 * ((t_sample)0.75));
			t_sample sub_321 = (mix_340 - mul_322);
			t_sample mul_320 = (sub_321 * ((t_sample)0.75));
			t_sample add_319 = (mul_320 + tap_324);
			t_sample tap_289 = m_delay_7.read_linear(mul_290);
			t_sample mul_287 = (tap_289 * ((t_sample)0.75));
			t_sample tap_317 = m_delay_6.read_linear(mul_318);
			t_sample mul_315 = (tap_317 * ((t_sample)0.75));
			t_sample mul_211 = (mul_199 * m_tail_24);
			t_sample mul_209 = (mul_197 * m_tail_24);
			t_sample add_195 = (mul_211 + mul_209);
			t_sample mul_210 = (mul_198 * m_tail_24);
			t_sample mul_208 = (mul_196 * m_tail_24);
			t_sample add_194 = (mul_210 + mul_208);
			t_sample sub_203 = (add_195 - add_194);
			t_sample mul_207 = (mul_254 * m_early_18);
			t_sample mul_205 = (mul_250 * m_early_18);
			t_sample add_193 = (mul_207 + mul_205);
			t_sample mul_206 = (mul_252 * m_early_18);
			t_sample mul_204 = (mul_248 * m_early_18);
			t_sample add_192 = (mul_206 + mul_204);
			t_sample sub_202 = (add_193 - add_192);
			t_sample add_189 = (sub_203 + sub_202);
			t_sample add_191 = (add_189 + in2);
			t_sample sub_286 = (add_191 - mul_287);
			t_sample mul_285 = (sub_286 * ((t_sample)0.75));
			t_sample add_284 = (mul_285 + tap_289);
			t_sample sub_279 = (add_284 - mul_280);
			t_sample mul_278 = (sub_279 * ((t_sample)0.625));
			t_sample add_277 = (mul_278 + tap_282);
			t_sample sub_272 = (add_277 - mul_273);
			t_sample mul_271 = (sub_272 * ((t_sample)0.625));
			t_sample add_270 = (mul_271 + tap_275);
			t_sample out2 = (add_270 + mul_188);
			t_sample add_201 = (add_189 + in1);
			t_sample sub_314 = (add_201 - mul_315);
			t_sample mul_313 = (sub_314 * ((t_sample)0.75));
			t_sample add_312 = (mul_313 + tap_317);
			t_sample sub_305 = (add_312 - mul_306);
			t_sample mul_304 = (sub_305 * ((t_sample)0.625));
			t_sample add_303 = (mul_304 + tap_308);
			t_sample sub_298 = (add_303 - mul_299);
			t_sample mul_297 = (sub_298 * ((t_sample)0.625));
			t_sample add_296 = (mul_297 + tap_301);
			t_sample out1 = (add_296 + mul_200);
			t_sample history_339_next_353 = fixdenorm(mix_340);
			t_sample history_227_next_354 = fixdenorm(mix_228);
			t_sample history_233_next_355 = fixdenorm(mix_234);
			t_sample history_239_next_356 = fixdenorm(mix_240);
			t_sample history_335_next_357 = fixdenorm(mix_336);
			m_delay_17.write(add_221);
			m_delay_16.write(add_222);
			m_delay_15.write(add_223);
			m_delay_14.write(add_224);
			m_delay_13.write(add_319);
			m_delay_12.write(sub_272);
			m_delay_11.write(sub_298);
			m_delay_10.write(sub_321);
			m_delay_9.write(sub_279);
			m_delay_8.write(sub_305);
			m_delay_7.write(sub_286);
			m_delay_6.write(sub_314);
			m_history_5 = history_339_next_353;
			m_history_4 = history_227_next_354;
			m_history_3 = history_233_next_355;
			m_history_2 = history_239_next_356;
			m_history_1 = history_335_next_357;
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_16.step();
			m_delay_17.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_early(t_param _value) {
		m_early_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_dry(t_param _value) {
		m_dry_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_spread(t_param _value) {
		m_spread_20 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_damping(t_param _value) {
		m_damping_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_roomsize(t_param _value) {
		m_roomsize_22 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_bandwidth(t_param _value) {
		m_bandwidth_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_tail(t_param _value) {
		m_tail_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_revtime(t_param _value) {
		m_revtime_25 = (_value < 0.1 ? 0.1 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 8; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_bandwidth(value); break;
		case 1: self->set_damping(value); break;
		case 2: self->set_dry(value); break;
		case 3: self->set_early(value); break;
		case 4: self->set_revtime(value); break;
		case 5: self->set_roomsize(value); break;
		case 6: self->set_spread(value); break;
		case 7: self->set_tail(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_bandwidth_23; break;
		case 1: *value = self->m_damping_21; break;
		case 2: *value = self->m_dry_19; break;
		case 3: *value = self->m_early_18; break;
		case 4: *value = self->m_revtime_25; break;
		case 5: *value = self->m_roomsize_22; break;
		case 6: *value = self->m_spread_20; break;
		case 7: *value = self->m_tail_24; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(8 * sizeof(ParamInfo));
	self->__commonstate.numparams = 8;
	// initialize parameter 0 ("m_bandwidth_23")
	pi = self->__commonstate.params + 0;
	pi->name = "bandwidth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_bandwidth_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_damping_21")
	pi = self->__commonstate.params + 1;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_dry_19")
	pi = self->__commonstate.params + 2;
	pi->name = "dry";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_dry_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_early_18")
	pi = self->__commonstate.params + 3;
	pi->name = "early";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_early_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_revtime_25")
	pi = self->__commonstate.params + 4;
	pi->name = "revtime";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_revtime_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_roomsize_22")
	pi = self->__commonstate.params + 5;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_spread_20")
	pi = self->__commonstate.params + 6;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_tail_24")
	pi = self->__commonstate.params + 7;
	pi->name = "tail";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tail_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_exported::
