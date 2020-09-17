<template>
  <div class="app-container">
    <CountySelector v-model="countyKey"/>
    <div class="filter=container">
      <el-input v-model="listQuery.title" placeholder="Title" style="width: 200px;" @key.enter.native="handleFilter" />
    </div>
    <el-table
      :data="list"
      border
      fit
      highlight-current-row
      style="width: 100%;"
      >
      <el-table-column label="序号" width="50px" align="center">
        <template slot-scope="{$index}">
          <span>{{ $index+1 }}</span>
        </template>
      </el-table-column>
      <el-table-column label="小区" width="100px" align="center">
        <template slot-scope="{row}">
          <span>{{ row.community }}</span>
        </template>
      </el-table-column> 

      <el-table-column label="栋" width="80px" align="center">
        <template slot-scope="{row}">
          <span>{{ row.buiding }}栋{{ row.room }}</span>
        </template>
      </el-table-column>

      <el-table-column label="规格" width="100px" align="center">
        <template slot-scope="{row}">
          <span>{{ row.nLivingroom }}厅{{ row.nToilet }}卫{{ row.nBedroom }}卧</span>
        </template>
      </el-table-column>

      <el-table-column label="面积" width="70px" align="center">
        <template slot-scope="{row}">
          <span>{{ row.area }} m&sup2</span>
        </template>
      </el-table-column>

      <el-table-column label="租金" width="60px" align="center">
        <template slot-scope="{row}">
          <span>{{ row.rent }}</span>
        </template>
      </el-table-column>

      <el-table-column label="操作" width="200px" align="center">
        <template slot-scope="{row,$index}">
          <el-button type="primary" size="mini" @click="leaseHousing(row)">租房</el-button>
          <el-button type="info" size="mini" @click="details(row)">查看详情</el-button>
        </template>
      </el-table-column>
    </el-table>
  </div>
</template>

<script>
  import CountySelector from './components/CountySelector'

  export default {
    name: 'LeaseHousing',
    components: {
      CountySelector
    },
    data() {
      return {
        list: null,
        countyKey: ' ',
        listQuery: {
          title: '',
          minRent: 0,
          maxRent: Infinity, 
        }
      }
    },
    watch: {
      countyKey: function() {
        this.getList()
      }
    },
    methods: {
      getList() {
        this.getRequest('/housings', {}).then(resp => {
          let list = resp.data
          let res = list.filter(item => item.city.includes(this.countyKey))
          this.list = res
        })
      },
      leaseHousing(item) {
        this.$router.push({ path: '/oms/addOrder', query: {
          housingId: item.id
        }})
      },
      details(item) {
        this.$router.push('/hms/housingDetails/' + item.id)
      },
      handleFilter() {

      }
    },
    created() {
      this.getList()
    }
  }
</script>