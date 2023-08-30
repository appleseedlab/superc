#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_40;
extern const bool __static_condition_default_41;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__filler_t_0", "filler_t");
__static_renaming("__some_fun_2", "some_fun");
__static_renaming("__f_3", "f");
__static_renaming("__f_4", "f");
__static_renaming("__shmem_get_inode_5", "shmem_get_inode");
__static_renaming("__ramfs_get_inode_6", "ramfs_get_inode");
__static_renaming("__shmem_file_setup_11", "shmem_file_setup");
__static_renaming("__drm_gem_object_init_13", "drm_gem_object_init");
__static_renaming("__i915_gem_alloc_object_16", "i915_gem_alloc_object");
__static_renaming("__do_read_cache_page_18", "do_read_cache_page");
__static_renaming("__filler_20", "filler");
__static_renaming("__read_cache_page_gfp_21", "read_cache_page_gfp");
__static_renaming("__i915_gem_object_get_pages_gtt_23", "i915_gem_object_get_pages_gtt");
__static_renaming("__i915_gem_object_bind_to_gtt_25", "i915_gem_object_bind_to_gtt");
__static_renaming("__i915_gem_object_pin_27", "i915_gem_object_pin");
__static_renaming("__intel_init_ring_buffer_29", "intel_init_ring_buffer");
__static_renaming("__intel_init_render_ring_buffer_31", "intel_init_render_ring_buffer");
__static_renaming("__i915_gem_init_ringbuffer_33", "i915_gem_init_ringbuffer");
__static_renaming("__i915_load_modeset_init_35", "i915_load_modeset_init");
__static_renaming("__readpage_36", "readpage");
__static_renaming("__i915_driver_load_37", "i915_driver_load");
__static_renaming("__main_38", "main");
__static_renaming("__main_39", "main");

__static_condition_renaming("__static_condition_default_7", "!(defined CONFIG_TMPFS) && (defined CONFIG_SHMEM) || (defined CONFIG_TMPFS)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_TMPFS)");
__static_condition_renaming("__static_condition_default_9", "!(defined CONFIG_TMPFS) && (defined CONFIG_SHMEM)");
__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_TMPFS) && !(defined CONFIG_SHMEM)");
__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_DRM_I915)");
__static_condition_renaming("__static_condition_default_40", "!(defined CONFIG_DRM_I915)");
__static_condition_renaming("__static_condition_default_41", "(defined CONFIG_DRM_I915)");

};
typedef int  (__filler_t_0) (int  );// L7

// typedef moved to top of scope
int  (__some_fun_2) (int  __n_1) {

{// L10
{



return  __n_1  ;// L11
}
}// L12


}
__filler_t_0  * (__f_4)= ( ( void  * ) 0 );// L17
__filler_t_0  * (__f_3)= &  __some_fun_2 ;// L15
__filler_t_0  * ((__shmem_get_inode_5) ()) {

{
if (__static_condition_default_7) {

{// L22
{



if (__static_condition_default_8) {
return  __f_3  ;// L23
}
if (__static_condition_default_9) {
return  __f_4  ;// L23
}
}
}// L24


}

}}
__filler_t_0  * ((__ramfs_get_inode_6) ()) {

{
if (__static_condition_default_10) {

{// L27
{



return &  __some_fun_2  ;// L28
}
}// L29


}

}}
__filler_t_0  * ((__shmem_file_setup_11) ()) {

{// L35
{



if (__static_condition_default_10) {
return  __ramfs_get_inode_6 ( ) ;// L36
}
if (__static_condition_default_7) {
return  __shmem_get_inode_5 ( ) ;// L36
}
}
}// L37


}
int  (__drm_gem_object_init_13) (__filler_t_0  * (* (__readpage_12))) {

if (__static_condition_default_14) {

{// L41
{



*  __readpage_12  =  __shmem_file_setup_11 ( ) ; // L42
return 0 ;// L43
}
}// L44


}
}
void  (__i915_gem_alloc_object_16) (__filler_t_0  * (* (__readpage_15))) {

if (__static_condition_default_14) {

{// L47
{



if (  __drm_gem_object_init_13  ( __readpage_15 ) != 0 )// L48
{
 ; // L49
}
}
}// L50


}
}
void  (__do_read_cache_page_18) (__filler_t_0  * (__filler_17)) {

if (__static_condition_default_14) {

{// L53
{



 __filler_17  (0) ; // L54
}
}// L55


}
}
void  (__read_cache_page_gfp_21) (__filler_t_0  * (* (__readpage_19))) {

if (__static_condition_default_14) {

{// L58
{



__filler_t_0  * (__filler_20)= *  __readpage_19 ;// L59

 __do_read_cache_page_18  ( __filler_20 ) ; // L60
}
}// L61


}
}
int  (__i915_gem_object_get_pages_gtt_23) (__filler_t_0  * (* (__readpage_22))) {

if (__static_condition_default_14) {

{// L64
{



 __read_cache_page_gfp_21  ( __readpage_22 ) ; // L65
return 0 ;// L66
}
}// L67


}
}
int  (__i915_gem_object_bind_to_gtt_25) (__filler_t_0  * (* (__readpage_24))) {

if (__static_condition_default_14) {

{// L70
{



return  __i915_gem_object_get_pages_gtt_23  ( __readpage_24 ) ;// L71
}
}// L72


}
}
int  (__i915_gem_object_pin_27) (__filler_t_0  * (* (__readpage_26))) {

if (__static_condition_default_14) {

{// L75
{



return  __i915_gem_object_bind_to_gtt_25  ( __readpage_26 ) ;// L76
}
}// L77


}
}
int  (__intel_init_ring_buffer_29) (__filler_t_0  * (* (__readpage_28))) {

if (__static_condition_default_14) {

{// L80
{



 __i915_gem_alloc_object_16  ( __readpage_28 ) ; // L81
return  __i915_gem_object_pin_27  ( __readpage_28 ) ;// L82
}
}// L83


}
}
int  (__intel_init_render_ring_buffer_31) (__filler_t_0  * (* (__readpage_30))) {

if (__static_condition_default_14) {

{// L86
{



return  __intel_init_ring_buffer_29  ( __readpage_30 ) ;// L87
}
}// L88


}
}
int  (__i915_gem_init_ringbuffer_33) (__filler_t_0  * (* (__readpage_32))) {

if (__static_condition_default_14) {

{// L91
{



return  __intel_init_render_ring_buffer_31  ( __readpage_32 ) ;// L92
}
}// L93


}
}
int  (__i915_load_modeset_init_35) (__filler_t_0  * (* (__readpage_34))) {

if (__static_condition_default_14) {

{// L96
{



return  __i915_gem_init_ringbuffer_33  ( __readpage_34 ) ;// L97
}
}// L98


}
}
int  (__i915_driver_load_37) () {

if (__static_condition_default_14) {

{// L101
{



__filler_t_0  * (__readpage_36);// L102

return  __i915_load_modeset_init_35  (&  __readpage_36 ) ;// L103
}
}// L104


}
}
int  (__main_38) () {

if (__static_condition_default_40) {

{// L108
{



return 0 ;// L112
}
}// L113


}
}
int  (__main_39) () {

if (__static_condition_default_41) {

{// L108
{



 __i915_driver_load_37 ( ) ; // L110
return 0 ;// L112
}
}// L113


}
}

