// Auto-generated file. Do not edit!
//   Template: src/f32-sigmoid/wasmsimd-lut64-p2-div.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


extern XNN_INTERNAL const float xnn_table_exp2minus_k_over_64[64];

void xnn_f32_sigmoid_ukernel__wasmsimd_lut64_p2_div_x20(
    size_t n,
    const float* x,
    float* y,
    const void* params) XNN_DISABLE_TSAN
{
  assert(n % sizeof(float) == 0);

  const v128_t vmagic_bias = wasm_f32x4_splat(0x1.800000p17f);
  const v128_t vminus_log2e = wasm_f32x4_splat(-0x1.715476p0f);
  const v128_t vindex_mask = wasm_i32x4_splat(INT32_C(0x3F));
  const v128_t vln2_hi = wasm_f32x4_splat(0x1.630000p-1f);
  const v128_t vln2_lo = wasm_f32x4_splat(-0x1.BD0106p-13f);
  const v128_t vc2 = wasm_f32x4_splat(0x1.FFFF0Ap-2f);
  const v128_t vone = wasm_f32x4_splat(1.0f);
  const v128_t vdenorm_cutoff = wasm_f32x4_splat(0x1.5D589Ep+6f);

  for (; n >= 20 * sizeof(float); n -= 20 * sizeof(float)) {
    const v128_t vx0123 = wasm_v128_load(x);
    const v128_t vx4567 = wasm_v128_load(x + 4);
    const v128_t vx89AB = wasm_v128_load(x + 8);
    const v128_t vxCDEF = wasm_v128_load(x + 12);
    const v128_t vxGHIJ = wasm_v128_load(x + 16);
    x += 20;

    const v128_t vz0123 = wasm_f32x4_abs(vx0123);
    const v128_t vz4567 = wasm_f32x4_abs(vx4567);
    const v128_t vz89AB = wasm_f32x4_abs(vx89AB);
    const v128_t vzCDEF = wasm_f32x4_abs(vxCDEF);
    const v128_t vzGHIJ = wasm_f32x4_abs(vxGHIJ);

    v128_t vn0123 = wasm_f32x4_add(vmagic_bias, wasm_f32x4_mul(vz0123, vminus_log2e));
    v128_t vn4567 = wasm_f32x4_add(vmagic_bias, wasm_f32x4_mul(vz4567, vminus_log2e));
    v128_t vn89AB = wasm_f32x4_add(vmagic_bias, wasm_f32x4_mul(vz89AB, vminus_log2e));
    v128_t vnCDEF = wasm_f32x4_add(vmagic_bias, wasm_f32x4_mul(vzCDEF, vminus_log2e));
    v128_t vnGHIJ = wasm_f32x4_add(vmagic_bias, wasm_f32x4_mul(vzGHIJ, vminus_log2e));

    const v128_t ve0123 = wasm_i32x4_shl(vn0123, 17);
    const v128_t ve4567 = wasm_i32x4_shl(vn4567, 17);
    const v128_t ve89AB = wasm_i32x4_shl(vn89AB, 17);
    const v128_t veCDEF = wasm_i32x4_shl(vnCDEF, 17);
    const v128_t veGHIJ = wasm_i32x4_shl(vnGHIJ, 17);

    const v128_t vidx0123 = wasm_i32x4_shl(wasm_v128_and(vn0123, vindex_mask), 2);
    const v128_t vidx4567 = wasm_i32x4_shl(wasm_v128_and(vn4567, vindex_mask), 2);
    const v128_t vidx89AB = wasm_i32x4_shl(wasm_v128_and(vn89AB, vindex_mask), 2);
    const v128_t vidxCDEF = wasm_i32x4_shl(wasm_v128_and(vnCDEF, vindex_mask), 2);
    const v128_t vidxGHIJ = wasm_i32x4_shl(wasm_v128_and(vnGHIJ, vindex_mask), 2);

    const uint64_t vidx01 = wasm_i64x2_extract_lane(vidx0123, 0);
    const uint64_t vidx23 = wasm_i64x2_extract_lane(vidx0123, 1);
    const v128_t vl0   = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx01));
    const v128_t vl2 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx23));
    const v128_t vl1 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx01 >> 32)));
    const v128_t vl3 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx23 >> 32)));
    const v128_t vl01 = wasm_v32x4_shuffle(vl0, vl1, 0, 4, 1, 5);
    const v128_t vl23 = wasm_v32x4_shuffle(vl2, vl3, 0, 4, 1, 5);
    const v128_t vl0123 = wasm_v32x4_shuffle(vl01, vl23, 0, 1, 4, 5);
    const uint64_t vidx45 = wasm_i64x2_extract_lane(vidx4567, 0);
    const uint64_t vidx67 = wasm_i64x2_extract_lane(vidx4567, 1);
    const v128_t vl4   = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx45));
    const v128_t vl6 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx67));
    const v128_t vl5 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx45 >> 32)));
    const v128_t vl7 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx67 >> 32)));
    const v128_t vl45 = wasm_v32x4_shuffle(vl4, vl5, 0, 4, 1, 5);
    const v128_t vl67 = wasm_v32x4_shuffle(vl6, vl7, 0, 4, 1, 5);
    const v128_t vl4567 = wasm_v32x4_shuffle(vl45, vl67, 0, 1, 4, 5);
    const uint64_t vidx89 = wasm_i64x2_extract_lane(vidx89AB, 0);
    const uint64_t vidxAB = wasm_i64x2_extract_lane(vidx89AB, 1);
    const v128_t vl8   = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx89));
    const v128_t vlA = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxAB));
    const v128_t vl9 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx89 >> 32)));
    const v128_t vlB = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxAB >> 32)));
    const v128_t vl89 = wasm_v32x4_shuffle(vl8, vl9, 0, 4, 1, 5);
    const v128_t vlAB = wasm_v32x4_shuffle(vlA, vlB, 0, 4, 1, 5);
    const v128_t vl89AB = wasm_v32x4_shuffle(vl89, vlAB, 0, 1, 4, 5);
    const uint64_t vidxCD = wasm_i64x2_extract_lane(vidxCDEF, 0);
    const uint64_t vidxEF = wasm_i64x2_extract_lane(vidxCDEF, 1);
    const v128_t vlC   = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxCD));
    const v128_t vlE = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxEF));
    const v128_t vlD = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxCD >> 32)));
    const v128_t vlF = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxEF >> 32)));
    const v128_t vlCD = wasm_v32x4_shuffle(vlC, vlD, 0, 4, 1, 5);
    const v128_t vlEF = wasm_v32x4_shuffle(vlE, vlF, 0, 4, 1, 5);
    const v128_t vlCDEF = wasm_v32x4_shuffle(vlCD, vlEF, 0, 1, 4, 5);
    const uint64_t vidxGH = wasm_i64x2_extract_lane(vidxGHIJ, 0);
    const uint64_t vidxIJ = wasm_i64x2_extract_lane(vidxGHIJ, 1);
    const v128_t vlG   = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxGH));
    const v128_t vlI = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxIJ));
    const v128_t vlH = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxGH >> 32)));
    const v128_t vlJ = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxIJ >> 32)));
    const v128_t vlGH = wasm_v32x4_shuffle(vlG, vlH, 0, 4, 1, 5);
    const v128_t vlIJ = wasm_v32x4_shuffle(vlI, vlJ, 0, 4, 1, 5);
    const v128_t vlGHIJ = wasm_v32x4_shuffle(vlGH, vlIJ, 0, 1, 4, 5);

    const v128_t vs0123 = wasm_i32x4_add(vl0123, ve0123);
    const v128_t vs4567 = wasm_i32x4_add(vl4567, ve4567);
    const v128_t vs89AB = wasm_i32x4_add(vl89AB, ve89AB);
    const v128_t vsCDEF = wasm_i32x4_add(vlCDEF, veCDEF);
    const v128_t vsGHIJ = wasm_i32x4_add(vlGHIJ, veGHIJ);

    vn0123 = wasm_f32x4_sub(vn0123, vmagic_bias);
    vn4567 = wasm_f32x4_sub(vn4567, vmagic_bias);
    vn89AB = wasm_f32x4_sub(vn89AB, vmagic_bias);
    vnCDEF = wasm_f32x4_sub(vnCDEF, vmagic_bias);
    vnGHIJ = wasm_f32x4_sub(vnGHIJ, vmagic_bias);

    v128_t vt0123 = wasm_f32x4_add(vz0123, wasm_f32x4_mul(vn0123, vln2_hi));
    v128_t vt4567 = wasm_f32x4_add(vz4567, wasm_f32x4_mul(vn4567, vln2_hi));
    v128_t vt89AB = wasm_f32x4_add(vz89AB, wasm_f32x4_mul(vn89AB, vln2_hi));
    v128_t vtCDEF = wasm_f32x4_add(vzCDEF, wasm_f32x4_mul(vnCDEF, vln2_hi));
    v128_t vtGHIJ = wasm_f32x4_add(vzGHIJ, wasm_f32x4_mul(vnGHIJ, vln2_hi));

    vt0123 = wasm_f32x4_add(vt0123, wasm_f32x4_mul(vn0123, vln2_lo));
    vt4567 = wasm_f32x4_add(vt4567, wasm_f32x4_mul(vn4567, vln2_lo));
    vt89AB = wasm_f32x4_add(vt89AB, wasm_f32x4_mul(vn89AB, vln2_lo));
    vtCDEF = wasm_f32x4_add(vtCDEF, wasm_f32x4_mul(vnCDEF, vln2_lo));
    vtGHIJ = wasm_f32x4_add(vtGHIJ, wasm_f32x4_mul(vnGHIJ, vln2_lo));

    v128_t vp0123 = wasm_f32x4_mul(vt0123, vc2);
    v128_t vp4567 = wasm_f32x4_mul(vt4567, vc2);
    v128_t vp89AB = wasm_f32x4_mul(vt89AB, vc2);
    v128_t vpCDEF = wasm_f32x4_mul(vtCDEF, vc2);
    v128_t vpGHIJ = wasm_f32x4_mul(vtGHIJ, vc2);

    vp0123 = wasm_f32x4_sub(vt0123, wasm_f32x4_mul(vp0123, vt0123));
    vp4567 = wasm_f32x4_sub(vt4567, wasm_f32x4_mul(vp4567, vt4567));
    vp89AB = wasm_f32x4_sub(vt89AB, wasm_f32x4_mul(vp89AB, vt89AB));
    vpCDEF = wasm_f32x4_sub(vtCDEF, wasm_f32x4_mul(vpCDEF, vtCDEF));
    vpGHIJ = wasm_f32x4_sub(vtGHIJ, wasm_f32x4_mul(vpGHIJ, vtGHIJ));

    const v128_t vy0123 = wasm_f32x4_sub(vs0123, wasm_f32x4_mul(vs0123, vp0123));
    const v128_t vy4567 = wasm_f32x4_sub(vs4567, wasm_f32x4_mul(vs4567, vp4567));
    const v128_t vy89AB = wasm_f32x4_sub(vs89AB, wasm_f32x4_mul(vs89AB, vp89AB));
    const v128_t vyCDEF = wasm_f32x4_sub(vsCDEF, wasm_f32x4_mul(vsCDEF, vpCDEF));
    const v128_t vyGHIJ = wasm_f32x4_sub(vsGHIJ, wasm_f32x4_mul(vsGHIJ, vpGHIJ));

    const v128_t vd0123 = wasm_f32x4_add(vy0123, vone);
    const v128_t vd4567 = wasm_f32x4_add(vy4567, vone);
    const v128_t vd89AB = wasm_f32x4_add(vy89AB, vone);
    const v128_t vdCDEF = wasm_f32x4_add(vyCDEF, vone);
    const v128_t vdGHIJ = wasm_f32x4_add(vyGHIJ, vone);

    v128_t vf0123 = wasm_f32x4_div(vy0123, vd0123);
    v128_t vf4567 = wasm_f32x4_div(vy4567, vd4567);
    v128_t vf89AB = wasm_f32x4_div(vy89AB, vd89AB);
    v128_t vfCDEF = wasm_f32x4_div(vyCDEF, vdCDEF);
    v128_t vfGHIJ = wasm_f32x4_div(vyGHIJ, vdGHIJ);

    vf0123 = wasm_v128_andnot(vf0123, wasm_f32x4_gt(vz0123, vdenorm_cutoff));
    vf4567 = wasm_v128_andnot(vf4567, wasm_f32x4_gt(vz4567, vdenorm_cutoff));
    vf89AB = wasm_v128_andnot(vf89AB, wasm_f32x4_gt(vz89AB, vdenorm_cutoff));
    vfCDEF = wasm_v128_andnot(vfCDEF, wasm_f32x4_gt(vzCDEF, vdenorm_cutoff));
    vfGHIJ = wasm_v128_andnot(vfGHIJ, wasm_f32x4_gt(vzGHIJ, vdenorm_cutoff));

    vf0123 = wasm_v128_bitselect(vf0123, wasm_f32x4_sub(vone, vf0123), wasm_i32x4_shr(vx0123, 31));
    vf4567 = wasm_v128_bitselect(vf4567, wasm_f32x4_sub(vone, vf4567), wasm_i32x4_shr(vx4567, 31));
    vf89AB = wasm_v128_bitselect(vf89AB, wasm_f32x4_sub(vone, vf89AB), wasm_i32x4_shr(vx89AB, 31));
    vfCDEF = wasm_v128_bitselect(vfCDEF, wasm_f32x4_sub(vone, vfCDEF), wasm_i32x4_shr(vxCDEF, 31));
    vfGHIJ = wasm_v128_bitselect(vfGHIJ, wasm_f32x4_sub(vone, vfGHIJ), wasm_i32x4_shr(vxGHIJ, 31));

    wasm_v128_store(y, vf0123);
    wasm_v128_store(y + 4, vf4567);
    wasm_v128_store(y + 8, vf89AB);
    wasm_v128_store(y + 12, vfCDEF);
    wasm_v128_store(y + 16, vfGHIJ);
    y += 20;
  }
  for (; n >= 4 * sizeof(float); n -= 4 * sizeof(float)) {
    const v128_t vx = wasm_v128_load(x);
    x += 4;

    const v128_t vz = wasm_f32x4_abs(vx);

    v128_t vn = wasm_f32x4_add(vmagic_bias, wasm_f32x4_mul(vz, vminus_log2e));
    const v128_t ve = wasm_i32x4_shl(vn, 17);

    const v128_t vidx = wasm_i32x4_shl(wasm_v128_and(vn, vindex_mask), 2);
    const uint64_t vidx_lo = wasm_i64x2_extract_lane(vidx, 0);
    const uint64_t vidx_hi = wasm_i64x2_extract_lane(vidx, 1);
    const v128_t vl0 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_lo));
    const v128_t vl1 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_lo >> 32)));
    const v128_t vl2 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_hi));
    const v128_t vl3 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_hi >> 32)));
    const v128_t vl_lo = wasm_v32x4_shuffle(vl0, vl1, 0, 4, 1, 5);
    const v128_t vl_hi = wasm_v32x4_shuffle(vl2, vl3, 0, 4, 1, 5);
    const v128_t vl = wasm_v32x4_shuffle(vl_lo, vl_hi, 0, 1, 4, 5);

    const v128_t vs = wasm_i32x4_add(vl, ve);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_add(vz, wasm_f32x4_mul(vn, vln2_hi));
    vt = wasm_f32x4_add(vt, wasm_f32x4_mul(vn, vln2_lo));

    v128_t vp = wasm_f32x4_mul(vt, vc2);
    vp = wasm_f32x4_sub(vt, wasm_f32x4_mul(vp, vt));

    const v128_t vy = wasm_f32x4_sub(vs, wasm_f32x4_mul(vs, vp));
    const v128_t vd = wasm_f32x4_add(vy, vone);

    v128_t vf = wasm_f32x4_div(vy, vd);
    vf = wasm_v128_andnot(vf, wasm_f32x4_gt(vz, vdenorm_cutoff));
    vf = wasm_v128_bitselect(vf, wasm_f32x4_sub(vone, vf), wasm_i32x4_shr(vx, 31));

    wasm_v128_store(y, vf);
    y += 4;
  }
  if XNN_UNLIKELY(n != 0) {
    const v128_t vx = wasm_v128_load(x);

    const v128_t vz = wasm_f32x4_abs(vx);

    v128_t vn = wasm_f32x4_add(vmagic_bias, wasm_f32x4_mul(vz, vminus_log2e));
    const v128_t ve = wasm_i32x4_shl(vn, 17);

    const v128_t vidx = wasm_i32x4_shl(wasm_v128_and(vn, vindex_mask), 2);
    const uint64_t vidx_lo = wasm_i64x2_extract_lane(vidx, 0);
    const uint64_t vidx_hi = wasm_i64x2_extract_lane(vidx, 1);
    const v128_t vl0 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_lo));
    const v128_t vl1 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_lo >> 32)));
    const v128_t vl2 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_hi));
    const v128_t vl3 = __builtin_wasm_load32_zero((int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_hi >> 32)));
    const v128_t vl_lo = wasm_v32x4_shuffle(vl0, vl1, 0, 4, 1, 5);
    const v128_t vl_hi = wasm_v32x4_shuffle(vl2, vl3, 0, 4, 1, 5);
    const v128_t vl = wasm_v32x4_shuffle(vl_lo, vl_hi, 0, 1, 4, 5);

    const v128_t vs = wasm_i32x4_add(vl, ve);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_add(vz, wasm_f32x4_mul(vn, vln2_hi));
    vt = wasm_f32x4_add(vt, wasm_f32x4_mul(vn, vln2_lo));

    v128_t vp = wasm_f32x4_mul(vt, vc2);
    vp = wasm_f32x4_sub(vt, wasm_f32x4_mul(vp, vt));

    const v128_t vy = wasm_f32x4_sub(vs, wasm_f32x4_mul(vs, vp));
    const v128_t vd = wasm_f32x4_add(vy, vone);

    v128_t vf = wasm_f32x4_div(vy, vd);
    vf = wasm_v128_andnot(vf, wasm_f32x4_gt(vz, vdenorm_cutoff));
    vf = wasm_v128_bitselect(vf, wasm_f32x4_sub(vone, vf), wasm_i32x4_shr(vx, 31));

    if (n & (2 * sizeof(float))) {
      *((double*) y) = wasm_f64x2_extract_lane(vf, 0);
      vf = wasm_v32x4_shuffle(vf, vf, 2, 3, 2, 3);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      *y = wasm_f32x4_extract_lane(vf, 0);
    }
  }
}
