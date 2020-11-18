// Auto-generated file. Do not edit!
//   Template: src/f32-dwconv2d-chw/3x3s2p1-wasmsimd-1x4-acc3.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>


#include <xnnpack/dwconv.h>
#include <xnnpack/math.h>



void xnn_f32_dwconv2d_chw_ukernel_3x3s2p1__wasmsimd_x86_1x4_acc3(
    size_t input_height,
    size_t input_width,
    const float* input,
    const float* weights,
    const float* zero,
    float* output,
    uint32_t padding_top,
    const union xnn_f32_chw_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(input_height != 0);
  assert(input_width != 0);
  assert(input_width % sizeof(float) == 0);
  assert(padding_top >= 0);
  assert(padding_top <= 1);

  const v128_t vmask_even = wasm_v128_load(params->scalar.mask_even);
  const v128_t vmask_odd  = wasm_v128_load(params->scalar.mask_odd);
  const v128_t vmax = wasm_v32x4_load_splat(&params->scalar.max);
  const v128_t vmin = wasm_v32x4_load_splat(&params->scalar.min);

  const v128_t vbias = wasm_v32x4_load_splat(weights);
  const v128_t vk00 = wasm_v32x4_load_splat(weights + 1);
  const v128_t vk01 = wasm_v32x4_load_splat(weights + 2);
  const v128_t vk02 = wasm_v32x4_load_splat(weights + 3);
  const v128_t vk10 = wasm_v32x4_load_splat(weights + 4);
  const v128_t vk11 = wasm_v32x4_load_splat(weights + 5);
  const v128_t vk12 = wasm_v32x4_load_splat(weights + 6);
  const v128_t vk20 = wasm_v32x4_load_splat(weights + 7);
  const v128_t vk21 = wasm_v32x4_load_splat(weights + 8);
  const v128_t vk22 = wasm_v32x4_load_splat(weights + 9);

  const size_t input_decrement = round_down_po2(input_width, 4 /* SIMD output width */ * 2 /* subsampling */ * sizeof(float));

  const float* i0 = (const float*) ((uintptr_t) input - ((-padding_top) & input_width));
  const float* i1 = (const float*) ((uintptr_t) i0 + input_width);
  if XNN_UNPREDICTABLE(padding_top != 0) {
    i0 = zero;
  }
  const float* i2 = (const float*) ((uintptr_t) i1 + input_width);

  size_t padded_input_height = input_height + padding_top + 1 /* padding bottom */;
  size_t output_height = (padded_input_height - 3 /* kernel size */ + 2 /* subsampling */) / 2;
  do {
    if XNN_UNPREDICTABLE(padded_input_height <= 3) {
      i2 = zero;
    }

    v128_t vi0x7531 = wasm_f32x4_splat(0.0f);
    v128_t vi1x7531 = wasm_f32x4_splat(0.0f);
    v128_t vi2x7531 = wasm_f32x4_splat(0.0f);

    size_t w = input_width;
    for (; w >= 8 * sizeof(float); w -= 8 * sizeof(float)) {
      v128_t vo8ACEp0 = vbias;

      const v128_t vi0x89AB = wasm_v128_load(i0);
      const v128_t vi1x89AB = wasm_v128_load(i1);
      const v128_t vi2x89AB = wasm_v128_load(i2);

      const v128_t vi0xCDEF = wasm_v128_load(i0 + 4);
      i0 += 8;
      const v128_t vi1xCDEF = wasm_v128_load(i1 + 4);
      i1 += 8;
      const v128_t vi2xCDEF = wasm_v128_load(i2 + 4);
      i2 += 8;

      const v128_t vi0x8ACE = wasm_v32x4_shuffle(vi0x89AB, vi0xCDEF, 0, 2, 4 + 0, 4 + 2);
      const v128_t vi0x9BDF = wasm_v32x4_shuffle(vi0x89AB, vi0xCDEF, 1, 3, 4 + 1, 4 + 3);
      const v128_t vi1x8ACE = wasm_v32x4_shuffle(vi1x89AB, vi1xCDEF, 0, 2, 4 + 0, 4 + 2);
      const v128_t vi1x9BDF = wasm_v32x4_shuffle(vi1x89AB, vi1xCDEF, 1, 3, 4 + 1, 4 + 3);
      const v128_t vi2x8ACE = wasm_v32x4_shuffle(vi2x89AB, vi2xCDEF, 0, 2, 4 + 0, 4 + 2);
      const v128_t vi2x9BDF = wasm_v32x4_shuffle(vi2x89AB, vi2xCDEF, 1, 3, 4 + 1, 4 + 3);

      vo8ACEp0 = wasm_f32x4_add(vo8ACEp0, wasm_f32x4_mul(vi0x8ACE, vk01));
      v128_t vo8ACEp1 = wasm_f32x4_mul(vi1x8ACE, vk11);
      v128_t vo8ACEp2 = wasm_f32x4_mul(vi2x8ACE, vk21);

      const v128_t vi0xF9BD = wasm_v32x4_shuffle(vi0x9BDF, vi0x9BDF, 3, 0, 1, 2);
      const v128_t vi1xF9BD = wasm_v32x4_shuffle(vi1x9BDF, vi1x9BDF, 3, 0, 1, 2);
      const v128_t vi2xF9BD = wasm_v32x4_shuffle(vi2x9BDF, vi2x9BDF, 3, 0, 1, 2);

      vo8ACEp0 = wasm_f32x4_add(vo8ACEp0, wasm_f32x4_mul(vi0x9BDF, vk02));
      vo8ACEp1 = wasm_f32x4_add(vo8ACEp1, wasm_f32x4_mul(vi1x9BDF, vk12));
      vo8ACEp2 = wasm_f32x4_add(vo8ACEp2, wasm_f32x4_mul(vi2x9BDF, vk22));

      const v128_t vi0x7BDF = wasm_v32x4_shuffle(vi0xF9BD, vi0x7531, 4, 1, 2, 3);
      const v128_t vi1x7BDF = wasm_v32x4_shuffle(vi1xF9BD, vi1x7531, 4, 1, 2, 3);
      const v128_t vi2x7BDF = wasm_v32x4_shuffle(vi2xF9BD, vi2x7531, 4, 1, 2, 3);

      vi0x7531 = vi0xF9BD;
      vi1x7531 = vi1xF9BD;
      vi2x7531 = vi2xF9BD;

      vo8ACEp0 = wasm_f32x4_add(vo8ACEp0, wasm_f32x4_mul(vi0x7BDF, vk00));
      vo8ACEp1 = wasm_f32x4_add(vo8ACEp1, wasm_f32x4_mul(vi1x7BDF, vk10));
      vo8ACEp2 = wasm_f32x4_add(vo8ACEp2, wasm_f32x4_mul(vi2x7BDF, vk20));

      v128_t vo = wasm_f32x4_add(vo8ACEp0, vo8ACEp1);
      vo = wasm_f32x4_add(vo, vo8ACEp2);

      vo = wasm_v128_bitselect(vmin, vo, wasm_f32x4_lt(vo, vmin));
      vo = wasm_v128_bitselect(vo, vmax, wasm_f32x4_le(vo, vmax));

      wasm_v128_store(output, vo);
      output += 4;
    }
    // Potentially process the last block of 0..7 pixels.
    assert(w < 8 * sizeof(float));
    if XNN_LIKELY(w != 0) {
      v128_t vo8ACEp0 = vbias;

      const v128_t vi0x89AB = wasm_v128_load(i0);
      const v128_t vi1x89AB = wasm_v128_load(i1);
      const v128_t vi2x89AB = wasm_v128_load(i2);

      const v128_t vi0xCDEF = wasm_v128_load(i0 + 4);
      const v128_t vi1xCDEF = wasm_v128_load(i1 + 4);
      const v128_t vi2xCDEF = wasm_v128_load(i2 + 4);

      const v128_t vi0x8ACE = wasm_v128_and(vmask_even, wasm_v32x4_shuffle(vi0x89AB, vi0xCDEF, 0, 2, 4 + 0, 4 + 2));
      const v128_t vi0x9BDF = wasm_v128_and(vmask_odd,  wasm_v32x4_shuffle(vi0x89AB, vi0xCDEF, 1, 3, 4 + 1, 4 + 3));
      const v128_t vi1x8ACE = wasm_v128_and(vmask_even, wasm_v32x4_shuffle(vi1x89AB, vi1xCDEF, 0, 2, 4 + 0, 4 + 2));
      const v128_t vi1x9BDF = wasm_v128_and(vmask_odd,  wasm_v32x4_shuffle(vi1x89AB, vi1xCDEF, 1, 3, 4 + 1, 4 + 3));
      const v128_t vi2x8ACE = wasm_v128_and(vmask_even, wasm_v32x4_shuffle(vi2x89AB, vi2xCDEF, 0, 2, 4 + 0, 4 + 2));
      const v128_t vi2x9BDF = wasm_v128_and(vmask_odd,  wasm_v32x4_shuffle(vi2x89AB, vi2xCDEF, 1, 3, 4 + 1, 4 + 3));

      vo8ACEp0 = wasm_f32x4_add(vo8ACEp0, wasm_f32x4_mul(vi0x8ACE, vk01));
      v128_t vo8ACEp1 = wasm_f32x4_mul(vi1x8ACE, vk11);
      v128_t vo8ACEp2 = wasm_f32x4_mul(vi2x8ACE, vk21);

      const v128_t vi0xF9BD = wasm_v32x4_shuffle(vi0x9BDF, vi0x9BDF, 3, 0, 1, 2);
      const v128_t vi1xF9BD = wasm_v32x4_shuffle(vi1x9BDF, vi1x9BDF, 3, 0, 1, 2);
      const v128_t vi2xF9BD = wasm_v32x4_shuffle(vi2x9BDF, vi2x9BDF, 3, 0, 1, 2);

      vo8ACEp0 = wasm_f32x4_add(vo8ACEp0, wasm_f32x4_mul(vi0x9BDF, vk02));
      vo8ACEp1 = wasm_f32x4_add(vo8ACEp1, wasm_f32x4_mul(vi1x9BDF, vk12));
      vo8ACEp2 = wasm_f32x4_add(vo8ACEp2, wasm_f32x4_mul(vi2x9BDF, vk22));

      const v128_t vi0x7BDF = wasm_v32x4_shuffle(vi0xF9BD, vi0x7531, 4, 1, 2, 3);
      const v128_t vi1x7BDF = wasm_v32x4_shuffle(vi1xF9BD, vi1x7531, 4, 1, 2, 3);
      const v128_t vi2x7BDF = wasm_v32x4_shuffle(vi2xF9BD, vi2x7531, 4, 1, 2, 3);

      vo8ACEp0 = wasm_f32x4_add(vo8ACEp0, wasm_f32x4_mul(vi0x7BDF, vk00));
      vo8ACEp1 = wasm_f32x4_add(vo8ACEp1, wasm_f32x4_mul(vi1x7BDF, vk10));
      vo8ACEp2 = wasm_f32x4_add(vo8ACEp2, wasm_f32x4_mul(vi2x7BDF, vk20));

      v128_t vo = wasm_f32x4_add(vo8ACEp0, vo8ACEp1);
      vo = wasm_f32x4_add(vo, vo8ACEp2);

      vo = wasm_v128_bitselect(vmin, vo, wasm_f32x4_lt(vo, vmin));
      vo = wasm_v128_bitselect(vo, vmax, wasm_f32x4_le(vo, vmax));

      if (w == 7 * sizeof(float)) {
        wasm_v128_store(output, vo);
        output += 4;
      } else {
        w += 1 * sizeof(float);
        if (w & (4 * sizeof(float))) {
          *((double*) output) = wasm_f64x2_extract_lane(vo, 0);
          output += 2;
          vo = wasm_v32x4_shuffle(vo, vo, 2, 3, 4 + 2, 4 + 3);
        }
        if (w & (2 * sizeof(float))) {
          *output = wasm_f32x4_extract_lane(vo, 0);
          output += 1;
        }
      }
    }

    i0 = (const float*) ((uintptr_t) i2 - input_decrement);
    i1 = (const float*) ((uintptr_t) i0 + input_width);
    i2 = (const float*) ((uintptr_t) i1 + input_width);

    output_height -= 1;
    padded_input_height -= 2;
  } while (output_height != 0);
}
