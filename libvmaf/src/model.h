/**
 *
 *  Copyright 2016-2020 Netflix, Inc.
 *
 *     Licensed under the BSD+Patent License (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *
 *         https://opensource.org/licenses/BSDplusPatent
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *
 */

#ifndef __VMAF_SRC_MODEL_H__
#define __VMAF_SRC_MODEL_H__

#include <stdbool.h>

enum VmafModelType {
    VMAF_MODEL_TYPE_UNKNOWN = 0,
    VMAF_MODEL_TYPE_SVM_NUSVR,
    VMAF_MODEL_BOOTSTRAP_SVM_NUSVR,
    VMAF_MODEL_RESIDUE_BOOTSTRAP_SVM_NUSVR,
};

enum VmafModelNormalizationType {
    VMAF_MODEL_NORMALIZATION_TYPE_UNKNOWN = 0,
    VMAF_MODEL_NORMALIZATION_TYPE_NONE,
    VMAF_MODEL_NORMALIZATION_TYPE_LINEAR_RESCALE,
};

typedef struct {
    char *name;
    double slope, intercept;
} VmafModelFeature;

typedef struct VmafModel {
    char *path;
    char *name;
    enum VmafModelType type;
    double slope, intercept;
    VmafModelFeature *feature;
    unsigned n_features;
    struct {
        bool enabled;
        double min, max;
    } score_clip;
    enum VmafModelNormalizationType norm_type;
    struct {
        bool enabled;
        struct {
            bool enabled;
            double value;
        } p0, p1, p2;
        bool out_lte_in, out_gte_in;
    } score_transform;
    struct svm_model *svm;
    struct {
        struct {
            bool enabled;
            double value;
        } adm_enhn_gain_limit, vif_enhn_gain_limit;
    } enhn_gain;
} VmafModel;

#endif /* __VMAF_SRC_MODEL_H__ */
