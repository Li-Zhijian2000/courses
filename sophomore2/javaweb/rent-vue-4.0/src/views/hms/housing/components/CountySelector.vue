<template>
  <div>
    <el-select v-model="valueProvince" placeholder="请选择省" @change="changeProvince">
      <el-option v-for="item in provinceList" :key="item.value" :label="item.label" :value="item.value">
      </el-option>
    </el-select>
    <el-select v-model="valueCity" placeholder="请选择市" @change="changeCity">
      <el-option v-for="item in cityOptions" :key="item.value" :label="item.label" :value="item.value">
      </el-option>
    </el-select>
    <el-button type="primary" size="mini" @click="$emit('input', selectedCounty)">确认</el-button>
    <el-button type="info" size="mini" @click="$emit('input', clear)">取消</el-button>
  </div>
</template>

<script>
  export default {
    name: 'CountySelector',
    props: {
      value: ''
    },
    data() {
      return {
        provinceList: [], // 省列表
        cityList: [], // 市列表
        valueProvince: '', // 所选的省
        valueCity: '', // 所选的市
        cityOptions: [], // 市下拉框数据
      }
    },
    computed: {
      selectedCounty() {
        const provinceIndex = this.provinceList.findIndex(({ value, label }) => value === this.valueProvince)
        const cityIndex = this.cityList.findIndex(({ value, label }) => value === this.valueCity)
        return this.provinceList[provinceIndex].label + ' ' + this.cityList[cityIndex].label //+ ' ' + this.originList[originIndex].label
      },
      clear() {
        return ''
      }
    },
    methods: {
      // 选择省
      changeProvince(val) {
        this.provinceList.forEach((province, index) => {
          if (val.toString() === this.provinceList[index].value) {
            this.cityOptions = this.provinceList[index].children
            this.valueCity = this.provinceList[index].children[0].value
            // this.originOptions = this.provinceList[index].children[0].children
            // this.valueOrigin = this.provinceList[index].children[0].children[0].value
          }
        })
      },
      // 选择市
      changeCity(val) {
        this.valueCity = val
      },
      _getJsonData() {
        this.getRequest('@/../public/china_address_v4.json').then((res) => {
          if (!res) console.log('error')
          this.provinceList = []
          this.cityList = []
          res.data.forEach((item) => {
            if (item.value.match(/0000$/)) {
              this.provinceList.push({
                value: item.value,
                label: item.name,
                children: []
              })
            } else if (item.value.match(/00$/)) {
              this.cityList.push({
                value: item.value,
                label: item.name,
              })
            }
          })
          for (let index in this.provinceList) {
            for (let index1 in this.cityList) {
              if (this.provinceList[index].value.slice(0, 2) === this.cityList[index1].value.slice(0, 2)) {
                this.provinceList[index].children.push(this.cityList[index1])
              }
            }
          }
        })
      }
    },
    created() {
      this._getJsonData()
    }
  }
</script>