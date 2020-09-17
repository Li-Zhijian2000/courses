<template>
  <el-card class="app-container" shadow="never">
    <div style="margin-top: 50px; margin: 0 auto; width: 500px">
      <el-form :model="orderForm" :rules="orderRules" size="small" label-position="left" label-width="100px">
        <el-form-item label="租赁方式: ">
          <el-select v-model="leaseType">
            <el-option v-for="item in options" :key="item.value" :label="item.label" :value="item.value"></el-option>
          </el-select>
        </el-form-item>

        <div v-if="leaseType === 'shortRent'">
          <el-form-item label="租房时长: ">
            <el-input v-model="orderForm.shortRentForm.day" placeholder="请选择天数"/>
          </el-form-item>
          <el-date-picker
            v-model="orderForm.shortRentForm.startDay"
            type="date"
            placeholder="选择起始日期"
            :picker-options="pickerOptions"
          />
        </div>
        <div v-else>
          <el-form-item label="租房时长: ">
            <el-input v-model="orderForm.longRentForm.month" placeholder="请选择月数"/>
          </el-form-item>
          <el-date-picker
            v-model="orderForm.longRentForm.startMonth"
            type="month"
            placeholder="选择起始月份"
            :picker-options="pickerOptions"
          />
        </div>
      </el-form>
    </div>
  </el-card>
</template>

<script>
  export default {
    data() {
      return {
        orderForm: {
          shortRentForm: {
            day: 0,
            startDay: ''
          },
          longRentForm: {
            month: 0,
            startMonth: ''
          }
        },
        orderRules: {

        },
        leaseType: 'shortRent',
        options: [
          {
            value: 'shortRent',
            label: '短租'
          },
          {
            value: 'longRent',
            label: '长租'
          }
        ],
        pickerOptions: {
          disabledDate(time) {
            return time.getTime() < Date.now()
          }
        }
      }
    },
    methods: {

    }
  }
</script>